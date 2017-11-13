/* PROGRAM: CST8234 C Lang; Assignment 4
   AUTHOR:  Tryton Van Meer
   DATE:    Dec 2015
   PURPOSE: A server/client application written in C in the form of a M.U.D game
*/

/**************************************************************************/
/* Define Header File
**************************************************************************/
#ifndef KOBOLD_H
#define KOBOLD_H


/**************************************************************************/
/* Declare include files
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <ncurses.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


/**************************************************************************/
/* Macro Defines
**************************************************************************/
/* kobold ->
 01101011 01101111 01100010 01101111 01101100 01100100 ->
 626F6C64 -> 62664 */
#define PORT 62664

/* Maximum number of clients kept queued if no connection is established */
#define NCLIENTS 6

/* Address of the server */
#define SERVER_ADDR "127.0.0.1"

/* Maximum length of a characters name */
#define MAXNAME 30

/* Maximum length of a rooms description */
#define MAXDESC 100

/* How long messages stay on screen in seconds */
#define MSGTIMER 3

/* Maximum size for a group of ememiese */
#define MAXMOB 5

/* Base stats */
#define BASEHP 10
#define BASEDEF 1
#define BASEATK 1


/*******************************************************************************
 * Protocol Codes
 *
 * The Kobold networking protocol is readable names that define
 * short handed strings for each command or response.
 *
 * PROTOMAX defines the maximun size of a buffer that holds these
 * protocol codes.
 *
 * 00-100+ are common commands
 * 400+    are errors
 *
 *
 * KOBOLD001   ->  GET_ROOM:  User has requested the current room they are in.
 *
 * KOBOLD000   -> POST_EXIT:   User is informing the server they are leaving.
 *
 * KOBOLD418  ->    TEAPOT:   Server response indicating that it is a teapot,
 *                            and unable to respond to the user's request as
*                             a Kobold server.
 ******************************************************************************/
#define PROTOMAX 8

#define POST_EXIT "KOB000"
#define GET_ROOM  "KOB001"
#define TEAPOT    "KOB418"






/**************************************************************************/
/* Structures
**************************************************************************/
typedef struct player
{
  int socket;
  char name[MAXNAME];
  int hp;
  int def;
  int atk;
  int xp;
  struct player *next;
} player_t;


struct room
{
  char desc[MAXDESC];
  char enemy[MAXNAME];
  int enemy_count;
};
typedef struct room room_t;

struct thread_args
{
  room_t *room;
  int new_socket;
};
typedef struct thread_args args_t;


/**************************************************************************/
/* Function prototypes
**************************************************************************/

/**************************************************************************
 * new_player
 * args:
 *    player_t *curr        - Pointer pointing current player
 *                           in linked list of players online.
 *    int client_socket    - Socket to assign to the player for communication
 *
 * Creates a new player in memory and sets the curr pointer to the
 * new players next pointer
 **************************************************************************/
player_t *new_player(int client_socket);


/**************************************************************************
 * error
 * args:
 *    char *msg - Message to pass to perror
 *
 * Calls perror and then exits with EXIT_FAILURE
 **************************************************************************/
void error(char *msg);


/**************************************************************************
 * main_menu
 *
 * Displays the splash screen and then the main menu
 * and waits till player chooses to join a game
 **************************************************************************/
int title_screen();


/**************************************************************************
 * sigint_handler
 *
 * Catches Ctrl-C and does some cleanup before exiting
 * Or prevents exiting in the client
 **************************************************************************/
void sigint_handler(int sig_num);


/**************************************************************************
 * get_player_name
 * args:
 *    int sockfd - Socket file descriptor to use for communication
 *
 * Gets the user to input a character name, and handles
 * writing to the socket.
 **************************************************************************/
int get_player_name(int sockfd);


/**************************************************************************
 * main_game
 * args:
 *    int sockfd - Socket file descriptor to use for communication
 *
 * Main instance of the game. Displays a menu for the player to select
 * from the in game options
 **************************************************************************/
int main_game(int sockfd);


/**************************************************************************
 * examine_room
 * args:
 *    int sockfd - Socket file descriptor to use for communication
 *
 * communicates with the server and displays to the player the current room
 * they are in. Return EXIT_FAILURE if the connection is broken
 **************************************************************************/
 int examine_room(int sockfd);


 /**************************************************************************
  * player_handler
  *
  * Function for handling each player. Is started in it's own thread for
  * each new player
  **************************************************************************/
void *player_handler(void *sock);


/**************************************************************************
 * display_net_err
 *
 * Displays a connection error message on a cleared screen
 **************************************************************************/
void display_net_err();


/**************************************************************************
 * generate_room
 *
 * Generates a new room and returns a pointer to it
 **************************************************************************/
room_t *generate_room();


// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
typedef struct { uint64_t state;  uint64_t inc; } pcg32_random_t;
uint32_t pcg32_random_r(pcg32_random_t* rng);

#endif /* KOBOLD_H */