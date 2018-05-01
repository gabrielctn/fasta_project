#include "../headers/dictionary.h"
#include "../headers/global.h"

Nucleic_Dict *tabNd;
int indexTabNd = 0;

// Détermine si le nucléotide actuel de la séquence analysée est correct ou non
int dicoNucleicIndex(char nucleotide) {
    switch (nucleotide) {
    case 'A':
        return 0;
        break;
    case 'C':
        return 1;
        break;
    case 'T':
        return 2;
        break;
    case 'G':
        return 3;
        break;
    default:
        err(EXIT_FAILURE, "Erreur: %c est un nucléotide inconnu au bataillon (A ou C ou T ou G) !", nucleotide);
    }
    return -1;
}

void insertDictionary(Nucleic_Dict *nd, char *sequence) {
    int index;

    ++(nd->nb);
    if (sequence[0] == '\0') {
        nd->end = 1;
    } else {
        index = dicoNucleicIndex(sequence[0]);
        if (nd->child[index] == NULL) {
            nd->child[index] = tabNd + (++indexTabNd);
        }
        insertDictionary(nd->child[index], sequence + 1);
    }
}

/* Parcours le dictionnaire récursivement pour voir
 * si la séquence recherchée s'y trouve */
int searchSeqDictionary(Nucleic_Dict *nd, char *sequence) {
    if (nd == NULL) {
        return 0;
    }
    if (sequence[0] == '\0') {
        return nd->end;
    }
    return searchSeqDictionary(nd->child[dicoNucleicIndex(sequence[0])], sequence + 1);
}

// Recherche le nombre de séquence qui ont le même préfixe demandé
int searchNbPrefixDictionary(Nucleic_Dict *nd, char *sequence) {
    if (nd == NULL) {
        return 0;
    }
    if (sequence[0] == '\0') {
        return nd->nb;
    }
    return searchNbPrefixDictionary(nd->child[dicoNucleicIndex(sequence[0])], sequence + 1);
}

/* Initialise le dictionnaire: enregistre tous les nucléotides de
 * toutes les séquences du fichier fasta */
void initNucleicDictionary(Nucleic_Dict *nd, Sequences *s) {
    if (s->next == NULL) {
        return;
    }
    insertDictionary(nd, s->sequence);
    initNucleicDictionary(nd, s->next);
}
