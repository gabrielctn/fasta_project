#include "headers/global.h"
#include "headers/sequences.h"

#define nbNucl 4
#define readLength 100
#define DEBUG 0

unsigned int generateRandom(int max) {
    int randVal;
    FILE *f;

    f = fopen("/dev/urandom", "r");
    do {
        fread(&randVal, sizeof(randVal), 1, f);
        randVal = abs(randVal % max);
    } while (randVal + readLength > max);
    fclose(f);
    return randVal;
}

char **generateReads(Sequences *seq) {
    int nbReads = 0;
    unsigned int rnd;
    size_t seqLength = strlen(seq->sequence);
    int k = seqLength * nbNucl / readLength;
    char **reads = (char **)calloc(k, sizeof(char *));

    printf("Génération des reads ...\n");

    while (nbReads < k - 2) {
        rnd = generateRandom(seqLength);
        reads[nbReads++] = strndup(seq->sequence + rnd, readLength);
        if (DEBUG) {
            printf("%s\n", reads[nbReads - 1]);
        }
    }
    /* On récupère explicitement le 1er et le dernier read
     * comme ils ont une probabilité plus faible d'être générés */
    reads[nbReads++] = strndup(seq->sequence, readLength);
    reads[nbReads] = strndup(seq->sequence + seqLength - readLength, readLength);

    printf("Taille de la séquence étudiée pour l'assemblage: %ld\n", seqLength);
    printf("Nombre de reads générés: %d\n", nbReads);
    return reads;
}
