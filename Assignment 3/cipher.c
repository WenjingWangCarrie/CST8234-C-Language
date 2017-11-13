/* 
   PROGRAM: Assignment 03A: Encryption Algorithms
   AUTHOR:  Wenjing Wang
   DATE:    2016-12-04
  
*/

/**************************************************************************/
/* Declare include files
**************************************************************************/
#include "cipher.h"

/**************************************************************************/
/* Declare main 
**************************************************************************/
int main(int argc, char **argv) {

    int opt;
    int key = 0;
    char *s_file = NULL;
    char *d_file = NULL;

    int decrypt = 0;
    int encrypt = 0;
    int help = 0;

    while ((opt = getopt(argc, argv, "hd:e:")) != -1) {
    	switch(opt) {
    		case 'h':
    		    help = 1;
    		    break;

    		case 'd':
    		    decrypt = 1;
    		    key = atoi(optarg);
    		    break;

    		case 'e':
    		    encrypt = 1;
    		    key = atoi(optarg);
    		    break;
    	}
    }

    /* set program name */
    pro = argv[0];

    /* check if key is integer */
    if (key == 0) {
    	printf("Key must be integer\n");
    	usage();
    	return EXIT_FAILURE;
    }

    /* chech source and destination argument */
    if (argv[optind] != NULL) {
    	s_file = argv[optind];

    	if (argv[optind+1] != NULL) {
    		d_file = argv[optind+1];
    	}
    }

    /* Arguments are not given */
    if (s_file == NULL || d_file == NULL) {
    	fprintf(stderr, "%s: Source and destination arguments should be given\n", argv[0]);

    }

    /* To check variables and encrypt/decrypt */
    if (help == 0 && decrypt == 0 && encrypt == 0) {
    	usage();
    	return EXIT_FAILURE;
    } else if (encrypt == 1 && decrypt == 1) {
    	fprintf(stderr, "encrypt and decrypt can't be used together.");
    } else if (help == 1) {
    	usage();
    	return EXIT_SUCCESS;
    } else if (decrypt == 1) {
    	printf("decrypting... %s\n", s_file);
    	crypt(0-key, s_file, d_file);
    	return EXIT_SUCCESS;
    } else if (encrypt == 1) {
    	printf("encrypting... %s\n", s_file);
    	crypt(key, s_file, d_file);
    	return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

/**************************************************************************
 * usage: prints help
**************************************************************************/
int usage() {
    printf("usage: %s [OPTION] [SOURCE] [DESTINATION]\n\n", pro);
    printf("options:\n");
    printf("-d KEY    %s\n", "decrypt the file SOURCE using KEY and writes back into DESTINATION");
    printf("-e KEY    %s\n", "encrypt the file SOURCE using KEY and writes back into DESTINATION");
    printf("-h        %s\n", "help in using the command");
    
    return EXIT_SUCCESS;
}

/**************************************************************************
 * crypt:
 * Encrypt/Decrypt a source file to a destination file using a KEY
 * SRC is the source file to encrypt or decrypt
 * DST is the file to write to
 * KEY is the decimal integer to use for decryption/encryption
 *
**************************************************************************/
int crypt(int KEY, char *SRC, char *DES) {
	FILE *sfile;
	FILE *dfile;
	int nextChar;
	int newChar;

	sfile = fopen(SRC, "r");
	dfile = fopen(DES,"w");

	if (sfile == NULL) {
		fprintf(stderr, "%s: [%s] could not be opened\n", pro, SRC);
		return EXIT_FAILURE;
	} else if (dfile == NULL) {
		fprintf(stderr, "%s: [%s] could not be opened\n", pro, DES);
		return EXIT_FAILURE;
	} 

	while ((nextChar = fgetc(sfile)) != EOF) {
		while (newChar < 0) {
			newChar += 256;
		}

		while (newChar > 255) {
			newChar -= 256;
		}

		fputc(newChar, dfile);
	}

	fclose(sfile);
	fclose(dfile);

	return EXIT_SUCCESS;

}
