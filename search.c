#include "headers/search.h"
#include "headers/global.h"

bool searchByGeneName(Sequences *s, char *geneName, int occ) {
    int i = 0, nbFound = 0;

    if (occ == 1) {
        printf("\nRecherche de la 1ere occurence de séquence nucléique dans la base, dont le nom du gène est \"%s\" :\n\n", geneName);
    } else if (occ == 0) {
        printf("\nRecherche de toutes les séquences nucléiques dans la base, dont le nom du gène est \"%s\" :\n\n", geneName);
    } else {
        printf("\nRecherche des %d premières occurences de séquences nucléiques dans la base, dont le nom du gène est \"%s\" :\n\n", occ, geneName);
    }

    while (s->next != NULL) {
        // Affiche toutes les séquences correspondantes (occ = 0) ou juste la 1ère (occ = 1)
        if ((occ == 0 || occ == 1) && strcmp(s->name, geneName) == 0) {
            printSeq(s);
            nbFound++;
            if (occ == 1) {
                return nbFound;
            }
        }
        // Affiche les n séquences correspondantes
        if ((occ > 1) && (strcmp(s->name, geneName) == 0) && (i++ < occ)) {
            printSeq(s);
            nbFound++;
        }
        s = s->next;
    }

    if (nbFound < occ) {
        printf("\nIl n'y a que %d occurences dans la base.\n\n", nbFound);
    }

    if (nbFound == FALSE) {
        printf("Désolé, aucune séquence ne correspond au gène %s\n\n", geneName);
    }

    return nbFound;
}

int searchBySequence(Sequences *seq, int occ, char *search) {
    char *rep;
    int nbseq = 0;

    if (seq == NULL) {
        return 0;
    }

    nbseq = searchBySequence(seq->next, occ, search);

    if (nbseq < occ || occ == 0) {                                    // tant que le nombre d'occurence n'a pas été trouvé ou si occ=0
        rep = strstr(seq->sequence, search);
        if (rep != NULL) {
            printf("La séquence recherchée a été trouvée dans la séquence %s\n", seq->name);
            return 1 + nbseq;
        }
    }
    return nbseq;
}

// Nécessaire de convertir la réponse de l'utilisateur en type enum
int searchByPosition(Sequences *seq, int occ, int position, enum chromosome_t chromosome) {
    int nbseq = 0;

    if (seq == NULL) {
        return 0;
    }

    nbseq = searchByPosition(seq->next, occ, position, chromosome);

    if (nbseq < occ || occ == 0) {
        if (seq->chromosome == chromosome &&
            seq->start < position && seq->end > position) {
            printf("La position %d recherchée a été trouvée dans la séquence %s\n", position, seq->name);
            return nbseq + 1;
        }
    }
    return nbseq;
}

void searchBySubSequence(Sequences *seq, int occ, char *search) {
    size_t i = 0, j = 0;
    int nbseq = 0;
    size_t lengthSequence, lengthSearch = strlen(search);

    printf("Recherche de la sous-séquence \"%s\" dans la base:\n\n", search);

    while (seq != NULL && (nbseq < occ || occ == 0)) {
        lengthSequence = strlen(seq->sequence);
        while (j < lengthSequence && i < lengthSearch) {
            if (seq->sequence[j] == search[i]) {
                i++;
            }
            j++;
        }
        // On regarde les conditions de sortie, si i>=length(sequence) on a trouvé la sous-séquence
        if (i >= lengthSearch) {
            nbseq++;
            printSeq(seq);
        }
        seq = seq->next;
        i = 0;
        j = 0;
    }

    if (nbseq == 0) {
        printf("Désolé, aucune séquence ne correspond à la sous-séquence %s\n", search);
    } else if (nbseq < occ) {
        printf("\nIl n'y a que %d occurences dans la base.\n", nbseq);
    }
}
