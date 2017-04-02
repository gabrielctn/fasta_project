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
void compare(char *protein, char *tmp, Code *tab, int k);
void translate(Sequences *seq, Menu *m);

#endif
