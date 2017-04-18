#include "headers/global.h"
#include "headers/sequences.h"
#include "headers/start.h"

void displayUsage() {
    printf("\n\n********** USAGE **********\n\n");
    printf("./projet\n\t");
    printf("[--help]\t\tPrint this help and exit\n\t");
    printf("[--nucleic]\t\tThe FASTA file contains nucleic sequences\n\t");
    printf("[--proteic]\t\tThe FASTA file contains proteic sequences\n\t");
    printf("[--file]\t\tGive the FASTA file. ex: S_pombe.fasta\n\t");
    printf("[--occurences]\t\tOptionnal. Number of sequences you whish to find/translate: 0 (all) or n. Default : all\n\t");
    printf("[--gene]\t\tSearch by gene name. ex: SPAC9E9.13.1\n\t");
    printf("[--sequence]\t\tSearch this specific sequence in the Sequences structure\n\t");
    printf("[--position]\t\tSearch sequences containing this position\n\t");
    printf("[--chromosome]\t\tSearch sequences from this chromosome\n\t");
    printf("[--subSequence]\t\tSearch sequences containing this sub-sequence. ex: \"ATCG\" -> A.*T.*C.*G\n\t");
    printf("[--dictSequence]\tSearch this specific sequence in the dictionary (containing all the sequences in the FASTA file)\n\t");
    printf("[--dictPrefix]\t\tUse the dictionary to search for all the sequences starting by this sequence\n\t");
    printf("[--translate]\t\tTranslate sequences in the FASTA file: nucleotides -> ARNm -> Protein\n\t");
    printf("[--codingSeq]\t\tSay if the sequences in the FASTA file are coding sequences or not: yes / no\n\n\n");
    printf("Examples:\n\t");
    printf("./projet_fasta --nucleic --file \"data/S_pombe.fasta\" --translate --codingSeq \"yes\" --occurences 8\n\t");
    printf("./projet_fasta --nucleic --file \"data/S_pombe.fasta\" --position 5000 --chromosome \"II\"\n\n");
    exit(EXIT_FAILURE);
}

FILE *openFile(Options *args) {
    FILE *fd;

    fd = fopen(args->file, "r");
    if (fd == NULL) {
        err(EXIT_FAILURE, "Erreur fopen: %s:", args->file);
    }
    return fd;
}

void freeOpt(Options *args) {
    free(args->file);
    free(args->gene);
    free(args->sequence);
    free(args->subSequence);
    free(args->dictSequence);
    free(args->dictPrefix);
    free(args->codingSeq);
    free(args);
}

void getOptions(int argc, char **argv, Options *args) {
    int c;

    if (argc == 1) {
        printf("\033[H\033[2J");
        displayUsage();
    }

    while (1) {
        static struct option long_options[] = {
            { "help",         no_argument,       0, 'h' },
            { "nucleic",      no_argument,       0, 'n' },
            { "proteic",      no_argument,       0, 'p' },
            { "file",         required_argument, 0, 'f' },
            { "occurences",   required_argument, 0, 'o' },
            { "gene",         required_argument, 0, 'g' },
            { "sequence",     required_argument, 0, 's' },
            { "position",     required_argument, 0, 'i' },
            { "chromosome",   required_argument, 0, 'c' },
            { "subSequence",  required_argument, 0, 'u' },
            { "dictSequence", required_argument, 0, 'd' },
            { "dictPrefix",   required_argument, 0, 'x' },
            { "translate",    no_argument,       0, 't' },
            { "codingSeq",    required_argument, 0, 'q' },
            {              0,                 0, 0,   0 }
        };
        /* getopt_long enregistre l'indice de l'option ici */
        int option_index = 0;

        c = getopt_long(argc, argv, "hnpf:o:g:s:i:u:d:x:tq:", long_options, &option_index);

        /* Détecte la fin des options */
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'h':
            printf("\033[H\033[2J");
            displayUsage();
        case 'n':
            args->nucleic = TRUE;
            break;
        case 'p':
            args->proteic = TRUE;
            break;
        case 'f':
            args->file = strdup(optarg);
            break;
        case 'o':
            args->occ = atoi(optarg);
            break;
        case 'g':
            args->gene = strdup(optarg);
            break;
        case 's':
            args->sequence = strdup(optarg);
            break;
        case 'i':
            args->position = atoi(optarg);
            break;
        case 'c':
            args->chromosome = str2enum(optarg);
            break;
        case 'u':
            args->subSequence = strdup(optarg);
            break;
        case 'd':
            args->dictSequence = strdup(optarg);
            break;
        case 'x':
            args->dictPrefix = strdup(optarg);
            break;
        case 't':
            args->translate = TRUE;
            break;
        case 'q':
            args->codingSeq = strdup(optarg);
            break;
        default:
            printf("\033[H\033[2J");
            displayUsage();
        }
    }

    /* Affiche les éléments restants (qui ne sont pas des options) */
    if (optind < argc) {
        printf("Cet élément n'est pas une option valable: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
    }
}

void checkArgs(Options *args) {
    if (!(args->nucleic || args->proteic)) {
        printf("\033[H\033[2J");
        printf("Attention, vous devez obligatoirement indiquer si les séquences sont protéiques ou nucléiques");
        displayUsage();
    }
    if (!args->file) {
        printf("\033[H\033[2J");
        printf("Attention, vous devez obligatoirement donner un fichier en argument");
        displayUsage();
    }
    if ((!args->translate && args->codingSeq) || (args->translate && !args->codingSeq)) {
        printf("\033[H\033[2J");
        printf("Attention, pour une traduction vous devez obligatoirement indiquer si les séquences sont codantes ou non (--translate et --codingSeq)");
        displayUsage();
    }
    if ((!args->position && (args->chromosome != 6)) || (args->position && (args->chromosome == 6))) {
        printf("\033[H\033[2J");
        printf("Attention, --position et --chromosome doivent obligatoirement être définis en même temps");
        displayUsage();
    }
}
