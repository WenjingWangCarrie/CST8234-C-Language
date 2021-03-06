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
int main (int argc, char **argv) {
    int opt;
    int key1, key2, key3, key4 = 0;
    char *s_file = NULL;
    char *d_file = NULL;

    int decrypt = 0;
    int encrypt = 0;
    int help = 0;

    while ((opt = getopt(argc, argv, "h:m:")) != -1) {
    	switch(opt) {
    		case 'h':
    		    help = 1;
    		    break;

    		case 'm':
    		    decrypt = 1;
    		    encrypt = 1;
    		    key1 = atoi(optarg);
    		    key2 = atoi(optarg);
    		    key3 = atoi(optarg);
    		    key4 = atoi(optarg);
    		    break;
    	}
    }

    /* set program name */
    pro = argv[0];

    /* check if key is integer */
    if (key1 == 0 || key2 == 0 || key3 == 0 || key4 == 0) {
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
    	hill(key1, key2, key3, key4, s_file, d_file, 'm');
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
    printf("-d KEY   %s\n", "decrypt the file SOURCE using KEY and writes back into DESTINATION");
    printf("-e KEY    %s\n", "encrypt the file SOURCE using KEY and writes back into DESTINATION");
    printf("-h        %s\n", "help in using the command");
    
    return EXIT_SUCCESS;
}

/**************************************************************************
 * hill:
 * Encrypt/Decrypt a source file to a destination file using a KEY
 * SRC is the source file to encrypt or decrypt
 * DST is the file to write to
 * KEY is the decimal integer to use for decryption/encryption
 *
**************************************************************************/
int hill(int KEY1, int KEY2, int KEY3, int KEY4, char *SRC, char *DES, char de) {
    FILE *sfile;
    FILE *dfile;
    int nextChar;
    int ans[25][1], mtrx[25][25];
    char txt[25];
    int size;
    int i, j;
    int sum, end;

    sfile = fopen(SRC, "r");
    dfile = fopen(DES,"w");

    if (sfile == NULL) {
	fprintf(stderr, "%s: [%s] could not be opened\n", pro, SRC);
	return EXIT_FAILURE;
    } else if (dfile == NULL) {
	fprintf(stderr, "%s: [%s] could not be opened\n", pro, DES);
	return EXIT_FAILURE;
    } 

    /* After open file, get file size, and move back to bbeginning */
    fseek(sfile, 0, SEEK_END);
    size = ftell(sfile);
    rewind(sfile);

    printf("\nEnter the string : ");
    scanf("%s",txt);

    for (i = 0; i < 25; i++) {
        if (txt[i] >= 97 && txt[i] < 122) {

        } else {
            end = i;
            break;
        }
    }

    for (i = 0; i < end; i++) {
        txt[i] = txt[i] - 'a';
    }

    printf("Enter matrix...");
    for (i = 0; i < end; i++) {
        for (j = 0; j < end; j++) {
            scanf("%d",&mtrx[i][j]);
        }
    }

    for (i = 0; i < end; i++) {
        sum = 0;
        for (j = 0; j < end; j++) {
            sum += mtrx[i][j]*(int)txt[j];
        }

        ans[i][0] = sum;
    }

    for (i = 0 ; i < end; i++) {
        printf("%c", ((ans[i][0])%26) + 97);
    }
	
	fclose(sfile);
	fclose(dfile);

	return EXIT_SUCCESS;
}




