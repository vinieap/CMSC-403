#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Because Givens.c wanted char * and fgetc return int
#define isDigit(c) (c >= '0' && c <= '9')
#define isLetter(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

//Function headers
int peekAhead(FILE *inf);
int readLetters(char *buffer, FILE *inf);
_Bool readDigits(char *buffer, FILE *inf);
struct lexics * nextLexic(FILE *inf);
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

#endif