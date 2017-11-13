/* PROGRAM:  01_Input.c 
   AUTHOR:   Wenjing Wang
   DATE:     Fall 2015
   TOPIC:    Basic C 
   PURPOSE:  01_Lab CST8234
   NOTES:   
             
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************************************/
/* Macro Defines
 **************************************************************************/
#define MIN 10;
#define MAX 100;

/**************************************************************************/
/* Function prototypes
 **************************************************************************/
int intGet( int , int );
int error( );

/**************************************************************************/
/* Global variables
 **************************************************************************/
int EFORMAT = 1;
int ECHARS = 2;
int ERANGE = 3;

int errorno = 0;

/**************************************************************************
 * Main
 *    Reads a number in between MIN and MAX from the keyboard
 *    Reports errors encountered 
 *    Returns 0 on success
 *            1 on failure
 **************************************************************************/
int main(void) {
    int num = intGet(10, 100);

    printf("Read %d\n", num);

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
int intGet(int min, int max) {
    char input[16];

    printf("Enter a number in between [%d-%d]: ", min, max);
    scanf("%s", &input);

    size_t ln = strlen(input);
    int i = 0;
    int dotCount = 0;
    int charCount = 0;

    for (i = 0; i < ln; i++) {
    	if (input[i] == '.') {
            dotCount++;
    	} else if (!isdigit(input[i])) {
        	charCount++;
        }
    }

    if (charCount != 0) {
        errorno = EFORMAT;
        error();
    } else if (dotCount != 0) {
        errorno = ECHARS;
        error();
    } else {
        int num = atoi(input);
        if (num < min || num > max) {
            errorno = ERANGE;
            error();
        } else {
            return num;
        }
    }	
}
/**************************************************************************/
/* error()
 *      Displays error message depening of errorno global variable
 *      Terminates with failure
 **************************************************************************/
int error() {
    if (errorno == EFORMAT) {
        printf("Incorrect input format\n");
    } else if (errorno == ECHARS) {
        printf("Extra characters\n");
    } else if (errorno == ERANGE) {
        printf("Input number out of range\n");
    }

    exit(EXIT_FAILURE);
}



