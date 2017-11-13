/*
 * Name:        iCount.c
 * Title:       the number of lines, words, characters in file
 * Descripts:   count the number of lines, words, characters in file
 * Author:      Wenjing Wang
 * Date:        2016-11-10
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
#define IN 1    /* inside a word */
#define OUT 0   /* outside a word */
#define BUFSIZE 1024

void displayStdResult(int lflag, int wflag, int cflag, int lines, int words, int characters, const char *prompt);
void displayExtraResult(int lines, const char *prompt);
void printUsage(const char *pgm);

int main(int argc, char *argv[]) {
    int lflag = 0;
    int wflag = 0;
    int cflag = 0;
    int pflag = 0;
    int iflag = 0;
    int vflag = 0;
    char *pvalue = NULL;

    int total_files = 0;
    int total_lines = 0;
    int total_words = 0;
    int total_characters = 0;
    int lines;
    int words;
    int characters;
    int ch;
    int n;
    int opt = 0;
    char buf[BUFSIZE];

    while ((opt = getopt(argc, argv, "hlwcivp:")) != -1) {
        switch (opt) {
            case 'l':
                lflag = 1;
                break;
            case 'w':
                wflag = 1;
                break;
            case 'c':
                cflag = 1;
                break;
            case 'p':
                pflag = 1;
                pvalue = optarg;
                break;
            case 'i':
                iflag = 1;
                break;
            case 'v':
                vflag = 1;
                break;
            case 'h':
                printUsage(argv[0]);
                exit(EXIT_FAILURE);
            case '?':
                if (optopt == 'p') {
                    printf("Option -%c requires an argument\n", optopt);
                } else {
                    printf("Unknown option -%c\n", optopt);
                }
                printUsage(argv[0]);
                exit(EXIT_FAILURE);
            default:
                printUsage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (lflag == 0 && wflag == 0 && cflag == 0) {
        lflag = 1;
        wflag = 1;
        cflag = 1;
    }

    if (optind == argc) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    for (n = optind; n < argc; n++) {
        FILE *fp = fopen(argv[n], "r");

        if (fp == NULL) {
            printf("Can't open file %s\n", argv[n]);
            exit(EXIT_FAILURE);
        }

        ++total_files;

        lines = 0;

        if (pflag == 1) {
            while (fgets(buf, sizeof(buf), fp) != NULL) {
                if (iflag == 1) {
                    if (vflag == 1) {
                        if (strcasestr(buf, pvalue) == '\0') {
                            ++lines;
                        }
                    } else {
                        if (strcasestr(buf, pvalue) != '\0') {
                            ++lines;
                        }
                    }
                } else {
                    if (vflag == 1) {
                        if (strstr(buf, pvalue) == NULL) {
                            ++lines;
                        }
                    } else {
                        if (strstr(buf, pvalue) != NULL) {
                            ++lines;
                        }
                    }
                }
            }
            total_lines += lines;

            displayExtraResult(lines, argv[n]);
        } else {
            words = 0;
            characters = 0;

          while ((ch = fgetc(fp)) != EOF) {
                
                if (ch != '\n' && ch != ' ') {
                    ++characters;
                }
                if (ch == ' ' || ch == '\n') {
                    ++words;
                } 
                if (ch == '\n') {
                    ++lines;
                }    
            }

            total_lines += lines;
            total_words += words;
            total_characters += characters;

            displayStdResult(lflag, wflag, cflag, lines, words, characters, argv[n]);
        }

        fclose(fp);
    }

    if (total_files == 0) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (total_files > 1) {
        if (pflag == 1) {
            displayExtraResult(total_lines, "total");
        } else {
            displayStdResult(lflag, wflag, cflag, total_lines, total_words, total_characters, "total");
        }
    }

    return EXIT_SUCCESS;
}

void displayStdResult(int lflag, int wflag, int cflag, int lines, int words, int characters, const char *prompt) {
    if (lflag == 1) {
        printf("%6d", lines);
    }
    if (wflag == 1) {
        printf("%6d", words);
    }
    if (cflag == 1) {
        printf("%6d", characters);
    }
    printf(" %s\n", prompt);
}

void displayExtraResult(int lines, const char *prompt) {
    printf("%6d %s\n", lines, prompt);
}

void printUsage(const char *pgm) {
    printf("Usage: %s [OPTION]... [FILE]...\n", pgm);
    printf("  -c prints the characters count\n");
    printf("  -w prints the word count\n");
    printf("  -l prints the newline count\n");
    printf("  -p prints the count of matching lines for the pattern\n");
    printf("  -h prints help\n");
}
