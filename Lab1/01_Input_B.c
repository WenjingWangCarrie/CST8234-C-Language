/* PROGRAM: 01_Input_B.c 
   AUTHOR:  Wenjing Wang
   DATE:    Sep 16,2016
   TOPIC:   Basic C 
   PURPOSE: 01_Lab CST8234
   NOTES:   
             
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************/
/* Macro Defines
 **************************************************************************/



/**************************************************************************/
/* Function prototypes
 **************************************************************************/
int intGet( );
int error( );


/**************************************************************************/
/* Global variables
 **************************************************************************/

int errorno;
int num;
/**************************************************************************
 * Main
 *    Reads a number in between MIN and MAX from the keyboard
 *    Reports errors encountered 
 *    Returns 0 on success
 *            1 on failure
 **************************************************************************/
int main( void ) {
    int min;
    int max;
    char c;
    int number = 0;
    int entry = 0;

    fscanf(stdin,"%d%d", &min, &max);
    printf("-----------------------------------------------\n");
    printf("    %dEntry    Invalid    Valid    %dNumber    \n", entry, number);
 
    while ((num = intGet()) != EOF) {

        printf ("Read %d\n", num);

        for (entry = 0; entry < 8; entry++) {
            printf("       %d               *             *        %d        \n", entry, number);
            if ((num > min) || (num < max)) {
                errorno = 3;
                error();
            } else if(c == '\n') {
                errorno = 2;
                error();
            } else {
              number++;
              return 0;
            }
           
         }    return num;

    }
    printf("-----------------------------------------------\n");
  
	 return EXIT_SUCCESS;
}

/**************************************************************************
 * intGet
 *      Read an integer number in between min and max
 *      Return: 
 *           number read
 *      Sets global variable errorno
 *           EFORMAT:  Incorrect format ( incorrect starts of characters )
 *           ECHARS :  Extra chars after the number
 *           ERANGE :  Number out of [ MIN, MAX ] range
 **************************************************************************/
int intGet() {
    char c;
    int file;

    file = fscanf(stdin, "%d%c", &num, &c);

    if (file == EOF) { 
        return EOF; 
    } else if (file != 0) {
        if (file == '\n' ) {
            return num;
        }
        else {
            return 0; 
        }       
    } else {
 
    fscanf(stdin, "%s", &c);
    return 0;
   }

}

/**************************************************************************/
/* error( )
 *      Displays error message depening of errorno global variable
 *      Terminates with failure
 **************************************************************************/
int error( ) {

    if (errorno==1) { 
        printf("Incorrect Format!\n");
    }
    else if (errorno==2) {
        printf("Extra charasters!\n");
    }
    else if ( errorno ==3) {
        printf("Number out of range!\n");
    }

    return EXIT_FAILURE; 
}

