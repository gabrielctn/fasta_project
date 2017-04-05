#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "search.h"
#include "start.h"

#define PROT_LINE_SIZE 60

typedef struct codeGenetic {
    char codon[4];     // le codon
    char acid;
} Code;

Code  *initialize();
int isARN(char *sequence);
char * transcription(char *sequence);
void compare(char *protein, char *tmp, Code *tab, int k);
void translate(Sequences *seq, Menu *m);
void freeCode(Code *tab);

#endif
