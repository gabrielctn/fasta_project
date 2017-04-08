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
int isNucleotide(char nucl);
void printing(char *sequence, int seq_idx, char *protein, int prot_idx, char *name, FILE *fd);
char *sequenceToTranslate(Sequences *seq, Menu *m, char *ARNm);
void verbose(Menu *m);
char *synthetizeProtein(int seq_idx, int prot_idx, char *sequence, Code *tab);

#endif
