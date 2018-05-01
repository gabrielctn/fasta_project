#include "../headers/global.h"
#include "../headers/search.h"
#include "../headers/start.h"
#include "../headers/dictionary.h"
#include "../headers/translate.h"
#include "../headers/assembly.h"

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
    double timeSpentAssemblingGenome;
    int res = 0;

    parseCommandLine(argc, argv, args);

    FILE *fd = openFile(args);

    clock_t begin = clock();
    if (args->assembly == TRUE && NULL == args->seqChoice) {
        displayUsage();
    }
    /* Lit le fichier FASTA et rempli la structure séquences */
    sequences = readSeq(fd, args);
    clock_t end = clock();
    double timeSpentReadingSeq = (double)(end - begin) / CLOCKS_PER_SEC;
    long totalLenSeq = totalLengthSequences(sequences);

    if (DEBUG) {
        printf("%ld\n", totalLenSeq);
    }

    /************************************** ASSEMBLAGE ********************************************
     **********************************************************************************************/
    if (args->assembly == TRUE) {
        CLEARSCR();
        Sequences *seq = searchSequenceToAssemble(args->seqChoice, sequences);
        if (seq == NULL) {
            err(EXIT_FAILURE, "La séquence recherchée n'est pas référencée dans la base\n\n");
        }
        clock_t begin = clock();
        char *genome = assembleGenome(seq);
        clock_t end = clock();
        timeSpentAssemblingGenome = (double)(end - begin) / CLOCKS_PER_SEC;
        writeGenome(genome, seq);
        printf("\n\n\n\n***************** ASSEMBLAGE DU GENOME *****************\n\n");
        if (checkAssembly(genome, seq->sequence)) {
            printf("Le génome a bien été assemblé !\n\n");
        } else {
            printf("Le génome assemblé ne correspond pas à la séquence initiale...\n\n\n");
            float sequenceCover = ((int)strlen(genome) * 100) / (int)strlen(seq->sequence);
            printf("Il ne couvre que %.2f %% du génome initial.\n\n", sequenceCover);
        }
        free(genome);
        printf("\n############## RAPPORT D'ACTIVITE DU PROGRAMME ##############\n");
        printf("\tTemps d'analyse des séquences du fichier: %.2f secondes\n", timeSpentReadingSeq);
        printf("\tTemps d'assemblage du génome: %.2f secondes\n", timeSpentAssemblingGenome);
    } else {
        /************************************** RECHERCHES ********************************************
         **********************************************************************************************/
        // initialise un tableau global de structures dictionnaire
        tabNd = (Nucleic_Dict *)calloc(totalLenSeq, sizeof(Nucleic_Dict));
        if (NULL == tabNd) {
            err(EXIT_FAILURE, "Erreur avec calloc du dictionnaire\n");
        }
        initNucleicDictionary(tabNd, sequences);
        // Affiche le menu et initialise la structure des variables du menu données par l'utilisateur
        CLEARSCR();
        do {
            choice = menu(m);
            CLEARSCR();
            switch (choice) {
            case 1:
                searchByGeneName(sequences, m->searchString, m->occ);
                break;
            case 2:
                res = searchBySequence(sequences, m->occ, m->searchString);
                if (res == 0) {
                    printf("Aucune séquence de la base ne contient la séquence que vous recherchez\n\n");
                } else if (res < m->occ) {
                    printf("\nIl n'y a que %d occurences dans la base\n", res);
                }
                break;
            case 3:
                res = searchByPosition(sequences, m->occ, m->position, m->chromosome);
                if (res == 0) {
                    printf("La position que vous cherchez ne se retrouve dans aucune séquence de la base\n\n");
                } else if (res < m->occ) {
                    printf("\nIl n'y a que %d occurences dans la base\n", res);
                }
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
            default:
                ;
            }
        } while (choice != 8);

        CLEARSCR();

        free(tabNd);
    }

    printf("\nAu revoir cher bioinformaticien ...\n\n");

    /* FREE ALL */
    freeSeq(sequences);
    freeOpt(args);
    freeMenu(m);

    fclose(fd);

    return 0;
}
