/* PROGRAM: CST8234 C Lang; Assignment 4
   AUTHOR:  Tryton Van Meer
   DATE:    Dec 2015
   PURPOSE: A server/client application written in C in the form of a M.U.D game
*/


#include "kobold.h"


void error(char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}