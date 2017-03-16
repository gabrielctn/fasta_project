#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "sequences.h"

typedef struct nucleic_dico {
    char final;
    struct nucleic_dico * child[4];
} Nucleic_Dico;


void initNucleicDictionary(Nucleic_Dico *nd, Sequences *s);
void insertDictionary(Nucleic_Dico *d, char *sequence);
int searchDictionary(Nucleic_Dico *nd, char *sequence);
int dicoNucleicIndex(Nucleic_Dico *nd, char nucleotide);

#endif
