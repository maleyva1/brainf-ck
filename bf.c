#include "bf.h"

int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("ERROR! No argument passed! Use --h to get help.\n");
        return 1;
    } else {
        char *filename = NULL;
        for(int i = 1; i < argc; i++) {
            if (strcmp((const char*)argv[i], "--h") == 0) {
                print_help();
            } else if(strncmp((const char *)argv[i], "--f", 3) == 0) {
                i++;
                filename = argv[i];
            } else {
                printf("ERROR! Argument passed is invalid! Use --h to get help.\n");
            }
        }
        
        if (filename != NULL) {
            // Initialize the tape
            int tape[TAPE_SIZE] = {0};
            int* ptr            = tape;
            char* file          = NULL;

            // Open the file
            FILE *f;
            f                   = fopen(filename, "r");
            // Exit if file can't be open
            if (f == NULL) {
                fprintf(stderr, "Can't open the file!\n");
                exit(1);
            }

            file = bf_ParseFile(f);
            int rc = bf_Interpret(file, tape);
            if (rc == 0) {
                printf("Success!\n");
            } else {
                printf("Failure!\n");
            }
            // Close file
            fclose(f);
            free(file);
        }
    }

    return 0;
}

int bf_Interpret(char* fp, int *turing)
{
    if (fp == NULL) {
        printf("Error parsing file.\n");
        return EXIT_FAILURE;
    }
    // char* ch = &fp[0];
    int tPointer = 0, chPointer = 0, chLength = strlen(fp);
    while(fp[chPointer] != '\0') {
        switch(fp[chPointer]) {
            case MOVE_PTR:
                ++tPointer;
                break;
            case DEC_PTR:
                --tPointer;
                break;
            case INC:
                if (tPointer < TAPE_SIZE && tPointer >= 0) {
                    ++turing[tPointer];
                } else {
                    return EXIT_FAILURE;
                }
                break;
            case DEC:
                if (tPointer < TAPE_SIZE && tPointer >= 0) {
                    --turing[tPointer];
                } else {
                    return EXIT_FAILURE;
                }
                break;
            case PRINT:
                if (tPointer < TAPE_SIZE && tPointer >= 0) {
                    putchar(turing[tPointer]);
                } else {
                    return EXIT_FAILURE;
                }
                break;
            case INPUT:
                if (tPointer < TAPE_SIZE && tPointer >= 0) {
                    turing[tPointer] = getchar();
                } else {
                    return EXIT_FAILURE;
                }
                break;
            case WHILE:
                if (tPointer < TAPE_SIZE && tPointer >= 0) {
                    if(turing[tPointer] == 0) {
                        int i = 1;
                        while(i > 0) {
                            if (chPointer < chLength && chPointer >= 0) {
                                chPointer++;
                            } else {
                                return EXIT_FAILURE;
                            }
                            switch(fp[chPointer]) {
                                case WHILE:
                                    i++;
                                    break;
                                case END_WHILE:
                                    i--;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                } else {
                    return EXIT_FAILURE;
                }
                break;
            case END_WHILE:
                if (tPointer < TAPE_SIZE && tPointer >= 0) {
                    if(turing[tPointer] != 0) {
                        int i = 1;
                        while(i > 0) {
                            if (chPointer < chLength && chPointer >= 0) {
                                chPointer--;
                            } else {
                                return EXIT_FAILURE;
                            }
                            switch(fp[chPointer]) {
                                case WHILE:
                                    i--;
                                    break;
                                case END_WHILE:
                                    i++;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
        if (chPointer < chLength && chPointer >= 0) {
            chPointer++;
        } else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

char* bf_ParseFile(FILE *fp)
{
    char *file = malloc(MAX_SIZE*sizeof(char));
    int i = 0, paran = 0;
    char ch;
    while((ch = fgetc(fp) ) > 0)
    {
        switch(ch) {
            case MOVE_PTR:
            case DEC_PTR:
            case INC:
            case DEC:
            case PRINT:
            case INPUT:
                file[i++] = ch;
                break;
            case WHILE:
                paran++;
                file[i++] = ch;
                break;
            case END_WHILE:
                paran--;
                file[i++] = ch;
                break;
            default:
                break;
                
        }
        if(i >= MAX_SIZE) {
            file = (char *)realloc(file, MAX_SIZE*sizeof(file));
        }
    }

    if (paran == 0) {
        file[i] = '\0';
        return file;
    } else {
        return NULL;
    }
}

void print_help(void)
{
    printf("Brainf*ck Interpretter\n");
    printf("Interprets Brainf*ck files.\n");
    printf("--h\t\tPrints out this menu\n");
    printf("--f FILENAME\tBrainf*ck file to interpret");
    printf("\n");
}