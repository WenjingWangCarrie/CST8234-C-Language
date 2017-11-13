/***********************
Include file
************************/
#include <stdio.h>
#include <sys/wait.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/**************************************************************************/
/* delimiter
 **************************************************************************/
#define SPACE " "

/**************************************************************************/
/* Prototype 
 **************************************************************************/
int MakeArg( char * buffer, char ***arg );


/**************************************************************************
 Main function
**************************************************************************/
int main(int argc,char* argv[]){
pid_t pid;
char s[60];
int length;
char** arg = NULL;

	while(1){
		printf("doit# ");
		fgets(s,60,stdin); 		/*gets the string*/
		length = strlen(s);
		s[length - 1] = '\0';		/*To replace \n with \0*/
		
		if( (strcmp(s,"q")) == 0)
		        exit(0);

		switch(pid = fork()){
	
		case -1:
			perror("FORK");
			exit(EXIT_FAILURE);
		case 0:
			
			MakeArg(s,&arg);
			execvp(*arg,arg);		

			perror("Exec");
			exit(EXIT_FAILURE);
			break;
		default:
		
			wait(NULL);
			break;
		}

	}
        return 0;
}
/**************************************************************************
PROGRAM:  MakeArg
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
