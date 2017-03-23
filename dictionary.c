#include "headers/dictionary.h"
#include "headers/global.h"


int dicoNucleicIndex(char nucleotide){

    switch(nucleotide){
        case 'A': return 0; break;
        case 'C': return 1; break;
        case 'T': return 2; break;
        case 'G': return 3; break;
        default:;
    }
    return -1;
}



void insertDictionary(Nucleic_Dict *nd, char *sequence){

    int index;
    ++(nd->nb);
    if(sequence[0] == '\0'){
        nd->end = 1;
    }
    else if((sequence[0] != 'A') && (sequence[0] != 'C') && (sequence[0] != 'T') && (sequence[0] != 'G'))
        err(EXIT_FAILURE, "Format de la séquence erroné (A ou C ou T ou G)");
    else{
        index = dicoNucleicIndex(sequence[0]);
        if(nd->child[index] == NULL){
            nd->child[index] = (Nucleic_Dict *) calloc(1, sizeof(Nucleic_Dict));
        }
        insertDictionary(nd->child[index], sequence+1);
    }
}



int searchSeqDictionary(Nucleic_Dict *nd, char *sequence){

    if(nd == NULL)
        return 0;
    if(sequence[0] == '\0')
        return nd->end;
    return searchSeqDictionary(nd->child[dicoNucleicIndex(sequence[0])], sequence+1);
}



int searchNbPrefixDictionary(Nucleic_Dict *nd, char *sequence){

    if(nd == NULL)
        return 0;
    if(sequence[0] == '\0')
        return nd->nb;
    return searchNbPrefixDictionary(nd->child[dicoNucleicIndex(sequence[0])], sequence+1);
}



void initNucleicDictionary(Nucleic_Dict *nd, Sequences *s){

    if(s->next == NULL)
        return;
    else
        insertDictionary(nd, s->sequence);
    initNucleicDictionary(nd, s->next);
}
