#include "headers/global.h"
#include "headers/sequences.h"
#include "headers/start.h"

#define CANONICAL 0
#define NON_CANONICAL 1

/* En mode non-canonical, le terminal accepte en entrée une chaîne > 4095 caractères */
void setTerminalMode(int mode) {
    struct termios settings;
    int parameters;

    parameters = tcgetattr(STDIN_FILENO, &settings);
    if (parameters < 0) {
        err(EXIT_FAILURE, "error in tcgetattr: cannot retrieve terminal's settings\n\n");
    }

    if (mode) {
        settings.c_lflag &= ~ICANON; // disable canonical mode
    } else {
        settings.c_lflag |= ICANON; // enable canonical mode
    }

    parameters = tcsetattr(STDIN_FILENO, TCSANOW, &settings);

    if (parameters < 0) {
        err(EXIT_FAILURE, "error in tcsetattr: cannot change terminal's mode\n\n");
    }
}

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

void displayUsage() {
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
        displayUsage();
    }

    while ((opt = getopt(argc, argv, "hn:p:")) != -1)
        switch (opt) {
        case 'h':
            displayUsage();
        case 'n':
            args->nucleic = TRUE;
            args->nuclFile = strdup(optarg);
            break;
        case 'p':
            args->proteic = TRUE;
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

char *getSring() {
    char *tmpLine;
    char c;
    int i = 0;
    char *line = (char *)calloc(1, sizeof(char));
    if (NULL == line) {
        err(EXIT_FAILURE, "Erreur avec calloc de line\n");
    }
    __fpurge(stdin); // vide le buffer
    while ((c = (char)getchar()) != '\n') {
        line[i++] = c;
        tmpLine = (char *)realloc(line, i + 1);
        if (NULL == tmpLine) {
            err(EXIT_FAILURE, "Erreur realloc getSequence\n");
        } else {
            line = tmpLine;
        }
    }
    line[i] = '\0';

    return line;
}

int menu(Menu *m) {
    int choice;

    printMenu();

    do {
        printf("\n\nQue voulez-vous faire ? : ");
        scanf("%d", &choice);
    } while (choice < 1 && choice > 8);

    switch (choice) {
    case 1:
        printf("Entrez le nom du gène: ");
        char *geneName = getSring();
        m->searchString = strdup(geneName);
        free(geneName);
        printf("Entrez le nombre d'occurences acceptées, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 2:
        printf("Entrez la séquence en 1 seule ligne, *** sans retours à la ligne ***: ");
        /* Change le mode d'entrée du terminal de canonical à non-canonical
         * pour accepter l'entrée de plus de 4095 bits */
        setTerminalMode(NON_CANONICAL);
        char *searchSequence = getSring();
        m->searchString = strdup(searchSequence);
        free(searchSequence);
        setTerminalMode(CANONICAL);
        printf("Entrez le nombre d'occurences acceptées, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 3:
        printf("Entrez la position: ");
        scanf("%d", &(m->position));
        printf("Entrez le chromosome dans lequel il est supposé être trouvé: ");
        char *chromosome = getSring();
        m->chromosome = str2enum(chromosome);
        free(chromosome);
        printf("Entrez le nombre d'occurences acceptées, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 4:
        printf("Entrez la sous-séquence: ");
        char *subSequence = getSring();
        m->searchString = strdup(subSequence);
        free(subSequence);
        printf("Entrez le nombre d'occurences acceptées, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    case 5:
        printf("Entrez la séquence en 1 seule ligne, *** sans retours à la ligne ***: ");
        /* Change le mode d'entrée du terminal de canonical à non-canonical
         * pour accepter l'entrée de plus de 4095 bits */
        setTerminalMode(NON_CANONICAL);
        char *dicoSearchSeq = getSring();
        m->searchString = strdup(dicoSearchSeq);
        free(dicoSearchSeq);
        setTerminalMode(CANONICAL);
        break;
    case 6:
        printf("Entrez le préfixe: ");
        char *dicoPrefixSearch = getSring();
        m->searchString = strdup(dicoPrefixSearch);
        free(dicoPrefixSearch);
        break;
    case 7:
        printf("Les séquences sont-elles codantes? (o/n): ");
        scanf(" %c", &(m->codingSeq));
        printf("Entrez le nombre d'occurences acceptées, toutes (0), 1 ou n : ");
        scanf("%d", &(m->occ));
        break;
    default:
        ;
    }
    printf("\n\n");

    return choice;
}
