/* PROGRAM: CST8234 C Lang; Assignment 4
   AUTHOR:  Tryton Van Meer
   DATE:    Dec 2015
   PURPOSE: A server/client application written in C in the form of a M.U.D game
*/


#include "kobold.h"


/**************************************************************************
 * Main
 *
**************************************************************************/
int main(int argc, char *argv[])
{
  int sockfd, clientfd;
  struct sockaddr_in serv_addr;
  struct sockaddr_storage cli_addr;
  socklen_t clilen;
  pthread_t tid;
  args_t *args;
  room_t *curr_room;

  /* Set signals */
  signal(SIGINT, sigint_handler);

  printf("KOBOLD (Server): Setting Up Server....\n");

  /* Create first room */
  curr_room = generate_room();

  /* Init args and set first room */
  args = malloc(sizeof(args_t));
  args->room = curr_room;

  /* Set up socket for communication */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    error("KOBOLD (SERVER): Network Error");
  }

  /* Initialize socket structure */
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);

  /* Bind socket */
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("KOBOLD (SERVER): Network Error");
  }

  printf("KOBOLD (SERVER): Listening for clients\n");

  /* Listen for connections */
  listen(sockfd, NCLIENTS);

  clilen = sizeof(struct sockaddr_in);

  while (true)
  {
    clientfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (clientfd < 0)
    {
      error("KOBOLD (SERVER): Network Error: error while accepting connection");
    }

    /* Insert players socket into args*/
    args->new_socket = clientfd;
    /* Start background thread for player */
    if ((pthread_create(&tid, NULL, player_handler, (void *) args)) < 0)
    {
      error("KOBOLD (Server): Thread Error");
    }
    pthread_detach(tid);
    //new_player(head, clientfd);
  }

  return EXIT_SUCCESS;
}

player_t *new_player(int client_socket)
{
  player_t *newp;

  newp = (player_t *)malloc(sizeof(player_t));

  /* Get player name */
  read(client_socket, newp->name, MAXNAME);

  /* Set stats to defualt*/
 newp->hp = BASEHP;
 newp->atk = BASEATK;
 newp->def = BASEDEF;

  /* Set the clients socket file desc */
  newp->socket = client_socket;

  printf("KOBOLD (SERVER): %s joined the server\n", newp->name);

  return newp;
}


void sigint_handler(int sig_num)
{
  printf("\rKOBOLD (SERVER): Exiting ~ BYE!\n");
  exit(EXIT_SUCCESS);
}

void *player_handler(void *args)
{
  char buff[PROTOMAX];
  player_t *p;
  room_t *curr_room;
  int stay_connected = 1;

  curr_room = ((args_t *) args)->room;
  p = new_player(((args_t *) args)->new_socket);

  /* Check each players socket for commands or if they left the server */
  while (stay_connected)
  {
    /* Read next packet from player. If unable to, exit. */
    if ((read(p->socket, buff, sizeof(buff))) <= 0)
    {
      printf("KOBOLD (SERVER): %s disconected\n", p->name);
      stay_connected = 0;
    }

    if (strcmp(POST_EXIT, buff) == 0)
    {
      printf("KOBOLD (SERVER): %s disconected\n", p->name);
      stay_connected = 0;
    }
    else if (strcmp(GET_ROOM, buff) == 0)
    {
      printf("KOBOLD (SERVER): %s -> GET_ROOM (%s)\n", p->name, GET_ROOM);
      write(p->socket, curr_room->desc, sizeof(char[MAXDESC]));
      printf("%s\n", curr_room->desc);
    }

    /* Clear buffer */
    memset(buff, 0, sizeof(buff));
  }

  free(p);
  pthread_exit(NULL);
}

room_t *generate_room()
{
  int randf;
  pcg32_random_t *randp;
  room_t *new_room;

  randf = open("/dev/random", O_RDONLY);
  new_room = malloc(sizeof(room_t));
  randp = malloc(sizeof(pcg32_random_t));

  read(randf, &randp->state, sizeof(uint64_t));
  read(randf, &randp->inc, sizeof(uint64_t));

  strcpy(new_room->enemy, "Kobold(s)");

  new_room->enemy_count = (pcg32_random_r(randp) % MAXMOB+1);

  if (new_room->enemy_count == 0)
  {
    strcpy(new_room->desc, "You're are in an empty room");
  }
  else
  {
    snprintf(new_room->desc, sizeof(new_room->desc),
    "You're are in a room with %d %s", new_room->enemy_count, new_room->enemy);
  }

  close(randf);
  return new_room;
}

uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}