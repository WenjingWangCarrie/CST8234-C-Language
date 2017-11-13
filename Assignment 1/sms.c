/* PROGRAM:  sms.c 
   AUTHOR:   Wenjing Wang
   DATE:     Fall 2016
   TOPIC:    C Programming
   PURPOSE:  Assignment 01 CST8234
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

#define MAX_MEM_SIZE  1000
#define INIT_MEMO    50505

#define TOO_BIG        -10
#define INVALID_WORD   -20
#define INVALID_CODE   -30
#define ADDRESSABILITY -40
#define DIVIDE_BY_ZERO -50
#define UNDERFLOW      -60
#define OVERFLOW       -70
#define ILLEGAL_INPUT  -80

#define END_OF_PROGRAM -999999

#define MIN_WORD -99999
#define MAX_WORD  99999

#define READ       10
#define WRITE      11
#define LOAD       20
#define STORE      21
#define ADD        30
#define SUBSTRACT  31
#define DIVIDE     32
#define MULTIPLY   33
#define BRANCH     40
#define BRANCHNEG  41
#define BRANCHZERO 42
#define HALT       43

/**************************************************************************/
/* Function prototypes
 **************************************************************************/

void init_memory(int *a, int size);
int load(int mem[], int max, int *total);
void dump(int *a, int total, int accumulator, int instCounter, 
          int instRegister, int operationCode, int operand, 
          int validInstructions);
void dump_memory(int* a, int max);
void error_message(int errorCode);

/**************************************************************************
 * Main
 *    Initializes the variables
 *    Reads an instruction file 
 *    Executes the instructions
 *    Returns 0 on success
 *            1 on failure
 **************************************************************************/
int main(void) {
    int *memory; /* Memory array */

    int accumulator = 0; /* accumulator */
    int instCounter = 0; /* Instruction Counter */
    int instRegister; /* Instruction Register */
    int operationCode; /* Operation Code */
    int operand; /* Operand */
    int validInstructions = 0; /* Valid Instructions */

    int maxMemo; /* Max Memory */
    int *mem; /* Memory Pointer */
    int on; /* Machine ON */

    memory = (int *)malloc(sizeof(int) * MAX_MEM_SIZE);  

    init_memory(memory, MAX_MEM_SIZE);

    int total = 0;
    int errorCode = load(memory, MAX_MEM_SIZE, &total);

    if (errorCode != 0) {
        error_message(errorCode);
        dump(memory, total, accumulator, instCounter, instRegister, operationCode, operand, validInstructions);

        return EXIT_FAILURE;
    }

    printf("********************************START EXECUTION********************************\n");

    int done = 0;
    int num = END_OF_PROGRAM;

    errorCode = EXIT_SUCCESS;

    while (!done) {
        if (instCounter >= total) {
            done = 1;
            break;
        }

        errorCode = EXIT_SUCCESS;

        /* fetch instruction */
        instRegister = memory[instCounter];
        operationCode = instRegister / 1000;
        operand = instRegister % 1000;

        //printf("instruction: %02d %03d\n", operationCode, operand);

        /* execute instruction */
        switch (operationCode) {
            case READ:
                /* Read a word into a specific memory location */
                fscanf(stdin, "%d", &num);
                printf("READ: %+06d\n", num);
                memory[operand] = num;
                break;
            case WRITE:
                /* Write a word in a specific memory location to the console */
                printf("%+06d\n", memory[operand]);
                break;
            case LOAD:
                /* Load a word from a specific memory location into the accumulator */
                accumulator = memory[operand];
                break;
            case STORE:
                /* Store the word in the accumulator to a specific memory location */
                memory[operand] = accumulator;
                break;
            case ADD:
                /* Add a word in a specific memory location to the word in the accumulator */
                accumulator = memory[operand] + accumulator;
                break;
            case SUBSTRACT:
                /* Subtract a word in a specific memory location by the word in the accumulator */
                accumulator = memory[operand] - accumulator;
                break;
            case DIVIDE:
                /* Divide a word in a specific memory location by the word in the accumulator */
                if (accumulator == 0) {
                    errorCode = DIVIDE_BY_ZERO;
                    done = 1;
                } else {
                    accumulator =  memory[operand] / accumulator;
                }
                break;
            case MULTIPLY:
                /* Multiply a word in a specific memory location by the word in the accumulator */
                accumulator =  memory[operand] * accumulator;
                break;
            case BRANCH:
                /* Branch to a specific memory location */
                instCounter = operand;
                break;
            case BRANCHNEG:
                /* Branch to a specific memory location if the accumulator is negative */
                if (accumulator < 0) {
                    instCounter = operand;
                }
                break;
            case BRANCHZERO:
                /* Branch to a specific memory location if the accumulator is zero */
                if (accumulator == 0) {
                    instCounter = operand;
                }
                break;
            case HALT:
                /* The program has completed its task */
                printf("******************************END EXECUTION******************************\n\n");
                done = 1;
                break;
            default:
                errorCode = INVALID_CODE;
                done = 1;
                break;
        } /* end switch */

        if (errorCode == EXIT_SUCCESS) {
            validInstructions++;
        }

        if (operationCode != BRANCH && 
            operationCode != BRANCHNEG && 
            operationCode != BRANCHZERO && 
            done != 1) {
            instCounter++;
        }
    } /* end while */

    if (errorCode != 0) {
        error_message(errorCode);
    }

    dump(memory, total, accumulator, instCounter, instRegister, operationCode, operand, validInstructions);

    return EXIT_SUCCESS;
}

void init_memory(int *a, int size) {
    int i;

    for (i = 0; i < size; i++) {
        a[i] = INIT_MEMO;
    }
}

int load(int *mem, int max, int *total) {
    int errorCode = EXIT_SUCCESS;
    int count = 0;
    int num;
    FILE *input = stdin;

    while (fscanf(input, "%d", &num) != EOF) {
        if (num == END_OF_PROGRAM) {
            /* End of program */
            break;
        }

        /* Verify it is a valid word */
        if (num < MIN_WORD || num > MAX_WORD) {
            errorCode = INVALID_WORD;
            break;
        }

        if (count < max) {
            mem[count] = num;
            count++;
        } else {
            errorCode = TOO_BIG;
            break;
        }
    }

    *total = count;

    return errorCode;
}

void dump(int *a, int total, int accumulator, int instCounter, int instRegister, int operationCode, int operand, int validInstructions) {
    printf("\n");
    printf("REGISTERS:\n");
    printf("accumulator         \t%+06d\n", accumulator);
    printf("Instruction Counter \t   %03d\n", instCounter);
    printf("Instruction Register\t%+06d\n", instRegister);
    printf("Operation Code      \t    %02d\n", operationCode);
    printf("Operand             \t   %03d\n", operand);
    printf("Valid Instructions  \t%6d\n", validInstructions);
    printf("\n\n");

    dump_memory(a, total);
}

void dump_memory(int *a, int max) {
    if (max == 0) {
        return;
    }

    int lines = max / 10;
    int reminder = max % 10;
    int i;
    int j;

    printf("MEMORY:\n\n");

    for (i = 0; i < lines; i++) {
        printf("%6d  ", i);
        for (j = 0; j < 10; j++) {
            printf("%+06d  ", a[i*10 + j]);
        }
        printf("\n");
    }

    if (reminder != 0) {
        printf("%6d  ", lines*10);
        for (j = 0; j < reminder; j++) {
            printf("%+06d  ", a[lines*10 + j]);
        }
        printf("\n");
    }
}

void error_message(int errorCode) {
    printf("\n");
    switch (errorCode) {
        case TOO_BIG:
            printf("*** ABEND: prg load: prg too big ***\n");
            break;
        case INVALID_WORD:
            printf("*** ABEND: prg load: invalid word ***\n");
            break;
        case INVALID_CODE:
            printf("*** ABEND: INVALID CODE ***\n");
            break;
        case ADDRESSABILITY:
            printf("*** ABEND: ADDRESSABILITY error ***\n");
            break;
        case DIVIDE_BY_ZERO:
            printf("*** ABEND: attempted division by 0 ***\n");
            break;
        case UNDERFLOW:
            printf("*** ABEND: underflow ***\n");
            break;
        case OVERFLOW:
            printf("*** ABEND: overflow ***\n");
            break;
        case ILLEGAL_INPUT:
            printf("*** ABEND: illegal input ***\n");
            break;
        default:
            printf("*** ABEND: unknown error ***\n");
            break;
    }
    printf("\n");
}

/* end of sms.c */

