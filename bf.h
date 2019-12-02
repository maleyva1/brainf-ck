#ifndef __BF_H__
#define __BF_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAPE_SIZE 300000
#define MAX_SIZE  1024

enum {
    MOVE_PTR = '>',
    DEC_PTR = '<',
    INC = '+',
    DEC = '-',
    PRINT = '.',
    INPUT = ',',
    WHILE = '[',
    END_WHILE = ']',
};

/* Brainfuck Parser */
char* bf_ParseFile(FILE *fp);
int bf_Interpret(char* fp, int* turing);
void print_help(void);

#endif