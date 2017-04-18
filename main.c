#include "headers/global.h"
#include "headers/search.h"
#include "headers/start.h"
#include "headers/dictionary.h"
#include "headers/translate.h"
#include "headers/sequences.h"

#define DEBUG 0

extern Nucleic_Dict *tabNd;

int main(int argc, char *argv[]) {
    /* Allocation des arguments en ligne de commande */
    Options *args = (Options *)calloc(1, sizeof(Options));
    if (NULL == args) {
        err(EXIT_FAILURE, "Erreur avec calloc de Options\n");
    }
    Sequences *sequences = NULL;
    int nbPrefix;

    args->nucleic = FALSE;
    args->proteic = FALSE;
    args->translate = FALSE;
    args->chromosome = 6;
    /* On récupère et vérifie les arguments données en ligne de comande */
    getOptions(argc, argv, args);
    // printf("%d %d\n", args->chromosome, args->position);
    checkArgs(args);

    FILE *fd = openFile(args);

    /* Lit le fichier FASTA et rempli la structure séquences */
    sequences = readSeq(fd);
    long totalLenSeq = totalLengthSequences(sequences);

    if (DEBUG) {
        printf("%ld\n", totalLenSeq);
    }

    // initialise un tableau global de structures dictionnaire
    tabNd = (Nucleic_Dict *)calloc(totalLenSeq, sizeof(Nucleic_Dict));
    if (NULL == tabNd) {
        err(EXIT_FAILURE, "Erreur avec calloc du dictionnaire\n");
    }

    initNucleicDictionary(tabNd, sequences);

    if (args->gene) {
        printf("Recherche du gène \"%s\" dans la base\n\n", args->gene);
        if (searchByGeneName(sequences, args->gene, args->occ) == 0) {
            printf("Désolé, aucune séquence ne correspond au gène %s\n\n", args->gene);
        }
    } else if (args->sequence) {
        printf("Recherche de la séquence \"%s\" dans la base\n\n", args->sequence);
        if (searchBySequence(sequences, args->occ, args->sequence) == 0) {
            printf("Désolé, la séquence n'a pas été trouvée dans la base\n\n");
        }
    } else if (args->subSequence) {
        printf("Recherche de la sous-séquence \"%s\" dans la base\n\n", args->subSequence);
        searchBySubSequence(sequences, args->occ, args->subSequence);
    } else if (args->position && (args->chromosome != 6)) {
        char *chr = enum2str(args->chromosome);
        printf("Recherche de la position %d avec un type chromosomique %s dans la base\n\n", args->position, chr);
        if (searchByPosition(sequences, args->occ, args->position, args->chromosome) == 0) {
            printf("Désolé, la position %d n'a été trouvée dans aucune séquence de type chromosomique %s\n\n", args->position, chr);
        }
        free(chr);
    } else if (args->dictSequence) {
        printf("Recherche de la séquence \"%s\" dans le dictionnaire\n\n", args->dictSequence);
        if (searchSeqDictionary(tabNd, args->dictSequence)) {
            printf("Trouvé ! La séquence se trouve dans le dictionnaire\n\n");
        } else {
            printf("Désolé, aucune séquence correspondante ne se trouve dans le dictionnaire\n\n");
        }
    } else if (args->dictPrefix) {
        printf("Recherche du nombre de séquences commençant par \"%s\" dans le dictionnaire\n\n", args->dictPrefix);
        nbPrefix = searchNbPrefixDictionary(tabNd, args->dictPrefix);
        if (nbPrefix) {
            printf("Il y a %d séquences dont \"%s\" est le préfix\n\n", nbPrefix, args->dictPrefix);
        } else {
            printf("Aucune séquence commence par \"%s\"\n\n", args->dictPrefix);
        }
    } else if (args->translate) {
        translate(sequences, args);
    }
    printf("\n\n");

    /* FREE ALL */
    freeSeq(sequences);
    freeOpt(args);
    free(tabNd);

    fclose(fd);

    return 0;
}
