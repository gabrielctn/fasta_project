#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "sequences.h"

typedef struct nucleic_dico {
    int nb; // nombre de séquences qui passent par ce nœud
    char end; // vaut 0 ou 1, si état final
    struct nucleic_dico * child[4];
} Nucleic_Dico;


void initNucleicDictionary(Nucleic_Dico *nd, Sequences *s);
void insertDictionary(Nucleic_Dico *d, char *sequence);
int searchSeqDictionary(Nucleic_Dico *nd, char *sequence);
int dicoNucleicIndex(Nucleic_Dico *nd, char nucleotide);
int searchNbPrefixDictionary(Nucleic_Dico *nd, char *sequence);

#endif
