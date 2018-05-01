#include "../headers/global.h"
#include "../headers/sequences.h"
#include "../headers/assembly.h"

#define NB_NUCL 5 // nombre moyen d'apparition de chaque base
#define READ_LENGTH 500000
#define READ_OVERLAP_LENGTH 50000
#define DEBUG 0

int nbReads = 0;

void printProgress(int percentage) {
    char pbstr[100] = "===================================================================================================";
    char pbstrf[103] = "[===================================================================================================>]";
    percentage++;
    char *bar = strndup(pbstr, percentage);
    if (percentage == 100) {
        printf("\33[2K\r");
        printf("\r %3d %% %s", percentage, pbstrf);
    } else {
        printf("\r %3d %% [%s>%*c]", percentage, bar, 99 - percentage, ' ');
    }
    fflush(stdout);
    free(bar);
}

// Génère aléatoirement le nombre de reads nécessaire
Read *generateReads(Sequences *seq, size_t seqLength) {
    int nbReads_idx = 0;
    unsigned int randomNb;
    Read *tabReads = (Read *)calloc(nbReads, sizeof(Read));

    while (nbReads_idx < nbReads - 2) {
        randomNb = generateRandom(seqLength);
        tabReads[nbReads_idx++].read = strndup(seq->sequence + randomNb, READ_LENGTH);
        if (DEBUG) {
            printf("%s\n", tabReads[nbReads_idx - 1].read);
        }
    }
    /* On récupère explicitement le 1er et le dernier read
     * comme ils ont une probabilité plus faible d'être générés */
    tabReads[nbReads_idx++].read = strndup(seq->sequence, READ_LENGTH);
    tabReads[nbReads_idx].read = strndup(seq->sequence + seqLength - READ_LENGTH, READ_LENGTH);

    printf("Taille de la séquence étudiée pour l'assemblage: %ld nucléotides\n", seqLength);
    printf("Génération des reads...\n\n");
    return tabReads;
}

unsigned int generateRandom(int max) {
    int randVal;
    FILE *f;

    f = fopen("/dev/urandom", "r");
    do {
        fread(&randVal, sizeof(randVal), 1, f);
        randVal = abs(randVal % max);
    } while (randVal + READ_LENGTH > max);
    fclose(f);
    return randVal;
}

/* Génère les reads, calcule les niveaux, dessine le graph orienté
 * et assemble les reads pour retrouver la séquence initiale */
char *assembleGenome(Sequences *seq) {
    Read *totalReads = mapReads(seq);
    int i = maxLevelRead(totalReads);
    int level = totalReads[i].level;
    char *genome = NULL;

    while (level >= 0) {
        char *readB = NULL, *preadB = NULL;
        int nextRead[2]; // permet de récupérer l'indice du prochain read à écrire et la taille du chevauchement entre les 2 reads

        if (level != 0) {
            searchLevel(level - 1, i, nextRead, totalReads);
        } else { // si le niveau est 0 dans le graph, on ne cherche pas de read chevauchant et on lui indique une taille de chevauchement nulle
            nextRead[0] = 0;
            nextRead[1] = 0;
        }

        readB = strndup(totalReads[i].read + nextRead[1], strlen(totalReads[i].read) - nextRead[1]); /* on prend le read sans la partie
                                                                                                      * chevauchante, pour fusionner les 2 reads */
        if (genome == NULL) {
            preadB = (char *)realloc(readB, strlen(readB) + 1);
        } else {
            preadB = (char *)realloc(readB, strlen(readB) + strlen(genome) + 1);
        }
        if (NULL == preadB) {
            err(EXIT_FAILURE, "Erreur realloc readB\n");
        } else {
            readB = preadB;
        }

        if (genome != NULL) {
            strcat(readB, genome);
        }
        char *pgenome = genome;
        genome = strdup(readB);
        free(pgenome);
        free(readB);

        if (level == 0) { // on a ajouté le dernier read du graphe orienté
            break;
        }
        i = nextRead[0];
        level = totalReads[i].level;
    }

    freeReads(totalReads);
    return genome;
}

// Génère le graph orienté des reads
Read *mapReads(Sequences *seq) {
    size_t seqLength = strlen(seq->sequence);
    nbReads = seqLength * NB_NUCL / READ_LENGTH;
    int i, j, nbCycles = 0;

    Read *totalReads = generateReads(seq, seqLength);
    while (nbCycles < nbReads) {    // on tourne le nombre de fois qu'il y a de read, si on tourne plus on contruirait un graphe en forme de cycle
        printProgress((int)(nbCycles * 100 / nbReads));
        for (i = 0; i < nbReads; i++) {
            for (j = 0; j < nbReads; j++) {
                if (i == j && i != nbReads - 1) { // On ne veut pas regarder un chevauchement d'un read sur lui-même
                    j++;
                }
                char *preadA = strdup(totalReads[i].read);
                char *prefix = strndup(totalReads[j].read, READ_OVERLAP_LENGTH);
                char *readA = strstr(preadA, prefix);      // recherche du préfixe dans le read
                int errFlag = overlap(readA, prefix, totalReads, j);
                if (errFlag == 0 && readA != NULL && strlen(readA) != READ_LENGTH) { // on a un chevauchement
                    if (totalReads[j].level < totalReads[i].level + 1) {     // on dessine le graph orienté des reads
                        totalReads[j].level = totalReads[i].level + 1;
                    }
                }
                free(preadA);
                free(prefix);
            }
        }
        nbCycles++;
    }
    printf("\n\n");
    printf("Nombre de reads générés: %d\n", nbReads);
    return totalReads;
}

int maxLevelRead(Read *totalReads) {
    int i = 0, max = 0, indexRead;

    for (i = 0; i < nbReads; i++) {
        if (totalReads[i].level > max) {
            max = totalReads[i].level;
            indexRead = i;
        }
    }
    return indexRead;
}

void searchLevel(int level, int index, int *nextRead, Read *totalReads) {
    int i;
    char *readA, *prefix;

    for (i = 0; i < nbReads; i++) {
        if (totalReads[i].level == level) {  // recherche read ayant le niveau inférieur
            readA = strdup(totalReads[i].read);
            prefix = strndup(totalReads[index].read, READ_OVERLAP_LENGTH);
            size_t nb = seekOverlap(readA, prefix, index, totalReads);
            if ((int)nb != 0) {     // si en plus le read a chevauchement avec le read du niveau supérieur
                nextRead[0] = i;    // indice du prochain read
                nextRead[1] = (int)nb; // taille du chevauchement entre les 2 reads
                break;
            }
        }
    }
    free(readA);
    free(prefix);
}

size_t seekOverlap(char *readA, char *prefix, int index, Read *totalReads) {
    readA = strstr(readA, prefix);
    int errFlag = overlap(readA, prefix, totalReads, index);
    if (errFlag == 0 && readA != NULL && strlen(readA) != READ_LENGTH) {
        return strlen(readA);
    }
    return 0;
}

int overlap(char *readA, char *prefix, Read *totalReads, int totalReads_idx) {
    int errFlag = 1, l;

    while (errFlag == 1 && readA != NULL) {
        errFlag = 0;
        if (readA != NULL) {
            for (l = 0; l < (int)strlen(readA); l++) {
                if (readA[l] != '\0' && readA[l] != totalReads[totalReads_idx].read[l]) {
                    errFlag = 1;
                    readA = strstr(readA + READ_OVERLAP_LENGTH, prefix);    // on regarde si le motif prefix se trouve ailleurs dans le read
                    break;
                }
            }
        }
    }
    return errFlag;
}

bool checkAssembly(char *genome, char *seq) {
    return !strcmp(genome, seq);
}

void writeGenome(char *genome, Sequences *seq) {
    FILE *fd = NULL;
    fd = fopen("data/assambly.txt", "w");

    if (NULL == fd) {
        err(EXIT_FAILURE, "Erreur fopen: assembly.txt:");
    }
    fprintf(fd, "SEQUENCE ASSEMBLEE: %s\n\n%s", seq->specialHeader, genome);
    fclose(fd);
}

Sequences *searchSequenceToAssemble(char *seqChoice, Sequences *seq) {
    if (seq == NULL) {
        return NULL;
    }
    if (strstr(seq->specialHeader, seqChoice) != NULL) {
        return seq;
    }
    return searchSequenceToAssemble(seqChoice, seq->next);
}

void freeReads(Read *totalReads) {
    int i;
    for (i = 0; i < nbReads; i++) {
        free(totalReads[i].read);
    }
    free(totalReads);
}
