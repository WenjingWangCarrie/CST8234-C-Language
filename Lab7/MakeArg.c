/* PROGRAM:  MakeArg
   AUTHOR:   Kay & Steven Robinson
	     Mod. by C Ayala 
   DATE:     20/11/15
   PURPOSE:  Parsing arguments
             To convert from char *s to char *arg[]
   NOTES:
   EXAMPLE:
             buffer --> "ls -l -a" 
	     argv   --> ls        
	            +-> l
                    +-> a
                    +-> NULL
*/

#include <stdio.h>
#include <sys/wait.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/**************************************************************************/
/* delimiter
 **************************************************************************/
#define SPACE " "

/**************************************************************************/
/* Prototype 
 **************************************************************************/
int MakeArg( char * buffer, char ***arg );

/**************************************************************************/
/* MakeArg
 **************************************************************************/
int MakeArg( char *s, char ***argvp ) {

char *t;
char *snew;
int numtokens;
int i;

/*
 * snew is real start of string after skipping leading delimiters
 */
snew = s + strspn( s, SPACE );

/*
 * Create space for a copy of snew in t 
 */
if (( t = calloc( strlen(snew) + 1, sizeof( char ) ) ) == NULL ) {
	*argvp = NULL;
	numtokens = -1;
}
else {
	/*
	 * Count the number of tokens in snew 
	 */
	strcpy( t, snew );
	if (strtok( t, SPACE ) == NULL )
		numtokens = 0;
	else
		for( numtokens = 1; strtok( NULL, SPACE ) != NULL; numtokens++ );
	/*
	 * Create an argument array to contain ptrs to tokens 
	 */
	if ((*argvp = calloc( numtokens + 1, sizeof( char *))) == NULL) {
		free( t);
		numtokens = -1;
	}
	else {
		/*
	 	* Insert pointers to tokens into the array 
	 	*/ 
		if (numtokens > 0 ) {
			strcpy( t, snew );
			**argvp = strtok( t, SPACE );
			/* If you need to see the array you are building:
		   	 * fprintf( stdout, "argvp[0] = %s\n",  **argvp );
			 */
			for( i = 1; i < numtokens + 1; i++ ) {
				*((*argvp) + i ) = strtok( NULL, SPACE );
			/* If you need to see the array you are building:
		   	 * fprintf( stdout, "argvp[%d] = %s\n", i, *((*argvp) + i ) );
			 */
			}
		}
		else {
			**argvp = NULL;
			free( t );
		}
	}
}
return ( numtokens );
}
