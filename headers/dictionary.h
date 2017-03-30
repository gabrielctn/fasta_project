#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "sequences.h"

typedef struct nucleic_dict
{
    int nb; // nombre de séquences qui passent par ce nœud
    char end; // vaut 0 ou 1, si état final
    struct nucleic_dict * child[4];
} Nucleic_Dict;


void initNucleicDictionary(Nucleic_Dict *nd, Sequences *s);
void insertDictionary(Nucleic_Dict *d, char *sequence);
int searchSeqDictionary(Nucleic_Dict *nd, char *sequence);
int dicoNucleicIndex(char nucleotide);
int searchNbPrefixDictionary(Nucleic_Dict *nd, char *sequence);

#endif
