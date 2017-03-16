#include "headers/dictionary.h"
#include "headers/global.h"


int dicoNucleicIndex(Nucleic_Dico *nd, char nucleotide){

    switch(nucleotide){
        case 'A':
            if(nd->child[0] == NULL) return 0; break;
        case 'C':
            if(nd->child[1] == NULL) return 1; break;
        case 'T':
            if(nd->child[2] == NULL) return 2; break;
        case 'G':
            if(nd->child[3] == NULL) return 3; break;
        default:;
    }
    return -1;
}
