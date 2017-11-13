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
  /* Kobold variables */

  /* Server/Client communication variables */
  int sockfd;
  struct sockaddr_in serv_addr;
  int game_state = 1;

  /* Init ncurses */
  initscr();
  clear();
  curs_set(FALSE);
  keypad(stdscr, TRUE);

  signal(SIGINT, sigint_handler);

  /* GAME START - NETWORKING */

  /* Initialize socket structure */
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);


  while (game_state)
  {
    /* (Re)Open socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      error("KOBOLD (CLIENT): Network Error");
    }

    if (title_screen() == EXIT_FAILURE)
    {
      game_state = 0;
    }
    else
    {
      /* Attempt connecting to server */
      if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        display_net_err();
      }
      else
      {
        /* Send data to server to create new player connection */
        if ((get_player_name(sockfd)) == EXIT_FAILURE)
        {
          /* Server connection break while inputing name */
          break;
        }

        /* Start the main game */
        main_game(sockfd);

        /* Tell server we are disconnecting */
        /* MSG_NOSIGNAL prevents SIGPIPES and we can close cleanly */
        if ((send(sockfd, POST_EXIT, PROTOMAX, MSG_NOSIGNAL)) > 0)
        {
          /* Close the socket */
          shutdown(sockfd, SHUT_RDWR);
          close(sockfd);
        }

        /* Go back to title screen*/
      }
    }
  }

  /* Shutdown program */
  clear();
  refresh();
  endwin();
  return EXIT_SUCCESS;
}


int title_screen()
{
  struct winsize w;
  int c;
  int i;
  int middle;
  char * SPLASH_ART[6];
  int menu_flag = 1;
  int option = 0;

  SPLASH_ART[0] = " _   _______ _     ______  _____ _    ______";
  SPLASH_ART[1] = "| | / /  _  | |    | ___ \\|  _  | |   |  _  \\";
  SPLASH_ART[2] = "| |/ /| | | | |    | |_/ /| | | | |   | | | |";
  SPLASH_ART[3] = "|    \\| | | | |    | ___ \\| | | | |   | | | |";
  SPLASH_ART[4] = "| |\\  \\ \\_/ / |____| |_/ /\\ \\_/ / |___| |/ /";
  SPLASH_ART[5] = "\\_| \\_/\\___/\\_____/\\____/  \\___/\\_____/___/";

  /* Get terminal size */
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  middle = (w.ws_col/2)-((w.ws_col/3)/2);

  clear();

  for (i=0; i<6; i++)
  {
    mvprintw(i, middle, SPLASH_ART[i]);
  }

  noecho();
  while(menu_flag == 1)
  {
    switch (option)
    {
      case 0:
        mvprintw(7, middle, "[*] JOIN GAME");
        mvprintw(8, middle, " *  EXIT");
        break;
      case 1:
        mvprintw(7, middle, " *  JOIN GAME");
        mvprintw(8, middle, "[*] EXIT");
        break;
    }

    refresh();
    c = getch();

    switch (c)
    {
      case 10:
      menu_flag = 0;
      break;

      case KEY_UP:
      option ^= 1;
      break;

      case KEY_DOWN:
      option ^= 1;
      break;
    }
  }

  if (option == 1)
  {
    return EXIT_FAILURE;
  }
  else if (option == 0)
  {
    mvprintw(10, middle+w.ws_col/10, "Finding a game...");
    refresh();
    sleep(MSGTIMER);
  }

  echo();
  return EXIT_SUCCESS;
}

int get_player_name(int sockfd)
{
  char new_name[MAXNAME];

  clear();
  refresh();

  mvprintw(0, 0, "Enter a name for your character: ");
  /* get user input */
  getstr(new_name);

  if ((send(sockfd, new_name, MAXNAME, MSG_NOSIGNAL)) < 0)
  {
    display_net_err();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main_game(int sockfd)
{
  int i;
  int c;

  const char * option_on = "[*]";
  const char * option_off = " * ";
  const char *options[2];
  const int option_count = 2;
  options[0] = "Examine Room";
  options[1] = "Exit";

  int selected_option = 0;
  int menu_flag = 1;

  while (menu_flag)
  {
    clear();

    for (i=0; i<option_count; i++)
    {
      /* Check Selected option print */
      if (i == selected_option)
      {
        mvprintw(i, 0, "%s %s", option_on, options[i]);
      }
      else
      {
        mvprintw(i, 0, "%s %s", option_off, options[i]);
      }
    }

    refresh();

    c = getch();
    switch (c)
    {
      case 10:
      switch (selected_option)
      {
        case 0:
        if (examine_room(sockfd) == EXIT_FAILURE)
        {
          menu_flag = 0;
          display_net_err();
        }
        break;

        case 1:
        menu_flag = 0;
        break;
      }
      break;

      case KEY_UP:
      selected_option += 1;
      if (selected_option > option_count-1) selected_option = 0;
      break;

      case KEY_DOWN:
      selected_option -= 1;
      if (selected_option < 0) selected_option = option_count-1;
      break;
    }
  }

  return EXIT_SUCCESS;
}

int examine_room(int sockfd)
{
  char room_desc[MAXDESC];

  clear();
  refresh();

  /* Get room description from server */
  /* Make sure connection isn't closed */
  if ((send(sockfd, GET_ROOM, PROTOMAX, MSG_NOSIGNAL)) < 0)
  {
    return EXIT_FAILURE;
  }
  else
  {
    read(sockfd, room_desc, sizeof(room_desc));

    mvprintw(0, 0, "%s", room_desc);
    refresh();
    sleep(MSGTIMER);
  }

  return EXIT_SUCCESS;
}

void sigint_handler(int sig_num)
{
  /* Ctrl-C is prevented from closing the program */
}

void display_net_err()
{
  clear();
  refresh();
  mvprintw(0, 0, "Unable to connect to server (Returning to main menu)");
  refresh();
  sleep(MSGTIMER);
}