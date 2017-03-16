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



void insertDictionary(Nucleic_Dico *nd, char *sequence){

    int index;

    if(sequence[0] == '\0')
        nd->final = 1;
    else if((sequence[0] != 'A') && (sequence[0] != 'C') && (sequence[0] != 'T') && (sequence[0] != 'G'))
        err(EXIT_FAILURE, "Format de la séquence erroné (A ou C ou T ou G)");
    else{
        index = dicoNucleicIndex(nd, sequence[0]);
        nd->child[index] = (Nucleic_Dico *) calloc(1, sizeof(Nucleic_Dico));
        insertDictionary(nd->child[index], sequence+1);
    }
}



int searchDictionary(Nucleic_Dico *nd, char *sequence){

    if(nd == NULL)
        return 0;
    if(sequence[0] == '\0')
        return nd->final;
    return searchDictionary(nd->child[dicoNucleicIndex(nd, sequence[0])], sequence+1);
}




void initNucleicDictionary(Nucleic_Dico *nd, Sequences *s){

    if(s->next == NULL)
        return;
    else
        insertDictionary(nd, s->sequence);
    initNucleicDictionary(nd, s->next);
}
