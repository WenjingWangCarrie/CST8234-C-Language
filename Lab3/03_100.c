/* PROGRAM:  03_100.c 
   AUTHOR:    
   DATE:     
   TOPIC:    Array Puzzles
   PURPOSE:  03_Lab CST8234
   NOTES:   
             
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************/
/* Defines
 **************************************************************************/
#define SIZE 100;

/**************************************************************************/
/* Function prototypes
**************************************************************************/
int toggle_door( char a[ ] );
int doors_state( char a[ ] ); 


/**************************************************************************
 * Main
 *    
 **************************************************************************/
int main( void ) {
   char array[100] = { 0 };
   
   toggle_door(array); 
   
   doors_state(array); 
   
   return EXIT_SUCCESS;
}

/**************************************************************************
 * Function: 
 **************************************************************************/

int toggle_door(char a[]) {
    int pass, door;
    
    /*do 100 passes */
    for (pass = 0; pass < 100; ++pass) {
        for (door = pass; door < 100; door += pass + 1) {
            a[door] = !a[door];
        }
    }  
    
    return 0;
}

int doors_state(char a[]) {
    int pass, door;
    
    /*display status of doors */
     for (door = 0; door < 100; ++door) {
        printf("    %s", (a[door] ? "1" : "0"));
    }
    
     printf("\n");
     return 0;
}
