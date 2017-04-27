#include "headers/global.h"
#include "headers/search.h"
#include "headers/start.h"
#include "headers/dictionary.h"
#include "headers/translate.h"
#include "headers/assembly.h"

#define DEBUG 0
#define CLEARSCR() printf("\033[H\033[2J");

extern Nucleic_Dict *tabNd;

int main(int argc, char *argv[]) {
    /* Allocation des arguments en ligne de commande
     * et de la structure contenant les variables du menu */
    Options *args = (Options *)calloc(1, sizeof(Options));
    if (NULL == args) {
        err(EXIT_FAILURE, "Erreur avec calloc de Options\n");
    }
    Menu *m = (Menu *)calloc(1, sizeof(Menu));
    if (NULL == m) {
        err(EXIT_FAILURE, "Erreur avec calloc de Menu\n");
    }
    Sequences *sequences = NULL;
    int nbPrefix;
    int choice;

    parseCommandLine(argc, argv, args);

    FILE *fd = openFile(args);

    /* Lit le fichier FASTA et rempli la structure séquences */
    sequences = readSeq(fd, args);

    long totalLenSeq = totalLengthSequences(sequences);

    if (DEBUG) {
        printf("%ld\n", totalLenSeq);
    }

    // initialise un tableau global de structures dictionnaire
    tabNd = (Nucleic_Dict *)calloc(totalLenSeq, sizeof(Nucleic_Dict));
    if (NULL == tabNd) {
        err(EXIT_FAILURE, "Erreur avec calloc du dictionnaire\n");
    }

    // initNucleicDictionary(tabNd, sequences);

    /* Affiche le menu et initialise la structure des variables du menu données par l'utilisateur */
    CLEARSCR();
    do {
        choice = menu(m, args);
        CLEARSCR();
        switch (choice) {
        case 1:
            searchByGeneName(sequences, m->searchString, m->occ);
            break;
        case 2:
            searchBySequence(sequences, m->occ, m->searchString);
            break;
        case 3:
            searchByPosition(sequences, m->occ, m->position, m->chromosome);
            break;
        case 4:
            searchBySubSequence(sequences, m->occ, m->searchString);
            break;
        case 5:
            printf("Recherche de la séquence \"%s\" dans le dictionnaire\n\n", m->searchString);
            if (searchSeqDictionary(tabNd, m->searchString)) {
                printf("Trouvé ! La séquence se trouve dans le dictionnaire\n\n");
            } else {
                printf("Désolé, aucune séquence correspondante ne se trouve dans le dictionnaire\n\n");
            }
            break;
        case 6:
            printf("Recherche du nombre de séquences commençant par \"%s\" dans le dictionnaire\n\n", m->searchString);
            if ((nbPrefix = searchNbPrefixDictionary(tabNd, m->searchString))) {
                printf("Il y a %d séquences dont \"%s\" est le préfix\n\n", nbPrefix, m->searchString);
            } else {
                printf("Aucune séquence commence par \"%s\"\n\n", m->searchString);
            }
            break;
        case 7:
            if (args->nucleic == TRUE) {
                translate(sequences, m);
            } else {
                printf("Fichier non nucléique, impossible de traduire\n");
            }
            break;
        case 8:
            if (args->assembly == TRUE) {
                char **totalReads = generateReads(sequences);
            }
            break;
        default:
            ;
        }
    } while (choice != 9);

    system("clear");
    printf("\nAu revoir cher bioinformaticien ...\n\n");

    /* FREE ALL */
    freeSeq(sequences);
    freeMenu(m);
    freeOpt(args);
    free(tabNd);

    fclose(fd);

    return 0;
}
