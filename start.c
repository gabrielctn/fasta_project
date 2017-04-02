#include "headers/global.h"
#include "headers/sequences.h"
#include "headers/start.h"

void printMenu() {
    printf("\n\n\n********************** Manipulation de séquences nucléiques ou protéiques **********************\n\n");
    printf("\tRECHERCHE GENERALE\n\n");
    printf("\t\t1. Par nom de gène\n");
    printf("\t\t2. Par séquence donnée\n");
    printf("\t\t3. Par position dans le génome\n");
    printf("\t\t4. Par sous-séquence\n\n");
    printf("\tRECHERCHE DANS LE DICTIONNAIRE\n\n");
    printf("\t\t5. Recherche de séquence dans le dictionnaire\n");
    printf("\t\t6. Recherche de séquences par préfixe dans le dictionnaire\n\n");
    printf("\tTRADUCTION\n\n");
    printf("\t\t7. Traduction de séquences nucléiques\n\n");
    printf("\t8. Quitter\n");
}

void display_usage() {
    printf("\n\n********** USAGE **********\n\n");
    printf("./projet [-h] or [-n NUCLEIC_FILENAME] or [-p PROTEIC_FILENAME]\n\n");

    printf("  -h	Print this help and exit\n");
    printf("  -n NUCLEIC_FILENAME	Work with a FASTA file containing nucleotide sequences\n");
    printf("  -p PROTEIC_FILENAME	Work with a FASTA file containing proteic sequences\n\n\n");

    exit(EXIT_FAILURE);
}

void parseCommandLine(int argc, char *argv[], Options *args) {
    char opt;
    int i;

    if (argc <= 1) {
        display_usage();
    }

    while ((opt = getopt(argc, argv, "hn:p:")) != -1)
        switch (opt) {
        case 'h':
            display_usage();
        case 'n':
            args->nucleic  = TRUE;
            args->nuclFile = strdup(optarg);
            break;
        case 'p':
            args->proteic  = TRUE;
            args->protFile = strdup(optarg);
            break;
        default:
            abort();
        }

    for (i = optind; i < argc; i++) {
        printf("Non-option argument %s\n", argv[i]);
    }
}

FILE *openFile(Options *args) {
    FILE *fd;

    if (args->nucleic == TRUE) {
        fd = fopen(args->nuclFile, "r");
        if (fd == NULL) {
            err(EXIT_FAILURE, "Erreur fopen: %s:", args->nuclFile);
        }
        return fd;
    } else {
        fd = fopen(args->protFile, "r");
        if (fd == NULL) {
            err(EXIT_FAILURE, "Erreur fopen: %s:", args->protFile);
        }
        return fd;
    }
}

void freeMenu(Menu *m) {
    free(m->searchString);
    free(m);
}

void freeOpt(Options *args) {
    free(args->nuclFile);
    free(args->protFile);
    free(args);
}

int menu(Menu *m) {
    int choice;
    char geneName[MAX_LENGTH_GENE_NAME];
    char searchSequence[MAX_LENGTH_SEARCH_SEQUENCE];
    char chromosome[MAX_LENGTH_CHROMOSOME];
    char subSequence[MAX_LENGTH_SUB_SEQUENCE];
    char dicoSearchSeq[MAX_LENGTH_DICO_SEARCH_SEQUENCE];
    char dicoPrefixSearch[MAX_LENGTH_DICO_PREFIX_SEARCH];

    printMenu();

    do {
        printf("\n\nQue voulez-vous faire ? : ");
        scanf("%d", &choice);
    } while (choice < 1 && choice > 8);

    switch (choice) {
    case 1:
        printf("Entrez le nom du gène: ");
        scanf("%s", geneName);
        m->searchString = strdup(geneName);
        printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 2:
        printf("Entrez la séquence (1000000 caractères max): ");
        scanf("%s", searchSequence);
        m->searchString = strdup(searchSequence);
        printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 3:
        printf("Entrez la position: ");
        scanf("%d", &(m->position));
        printf("Entrez le chromosome dans lequel il est supposé être trouvé: ");
        scanf("%s", chromosome);
        m->chromosome = str2enum(chromosome);
        printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 4:
        printf("Entrez la séquence (100 caractères max): ");
        scanf("%s", subSequence);
        m->searchString = strdup(subSequence);
        printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 5:
        printf("Entrez la séquence en 1 seule ligne, sans retours à la ligne (1000000 caractères max): ");
        scanf("%s", dicoSearchSeq);
        m->searchString = strdup(dicoSearchSeq);
        break;
    case 6:
        printf("Entrez le préfixe (100 caractères max): ");
        scanf("%s", dicoPrefixSearch);
        m->searchString = strdup(dicoPrefixSearch);
        break;
    case 7:
        break;
    default:
        ;
    }
    printf("\n\n");

    return choice;
}
