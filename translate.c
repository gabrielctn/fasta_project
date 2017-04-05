#include "headers/translate.h"
#include "headers/global.h"

Code *initialize() {
    int i;
    Code *tab = (Code *)calloc(64, sizeof(Code));
    FILE *fd  = fopen("codegenetic.txt", "r");

    if (fd == NULL) {
        err(EXIT_FAILURE, "Erreur fopen: codegenetic.txt:");
    }

    for (i = 0; i < 64; i++) {
        fscanf(fd, "%c %s\n", &(tab[i].acid), tab[i].codon);
    }
    fclose(fd);
    return tab;
}

int isARN(char *sequence) {
    if (strstr(sequence, "U") == NULL) {        // Si on a trouvé un U dans la séquence, on a une séquence d'ARN, on peut donc traduire directement
        return 0;
    }
    return 1;
}

char *transcription(char *sequence) {
    size_t seq_length, i;

    seq_length = strlen(sequence);
    char *inversion = (char *)malloc(seq_length + 1);

    // Transcription: l'ADN est transformé en ARN pour pouvoir être traduite
    // Les T deviennent des A et les C des G et inversement
    for (i = 0; i < seq_length; i++) {
        if (sequence[i] == 'A') {
            inversion[seq_length - i - 1] = 'U';                // METTRE DANS UNE FONCTION CAR REPETITION 4 FOIS
        } else if (sequence[i] == 'T') {
            inversion[seq_length - i - 1] = 'A';
        } else if (sequence[i] == 'C') {
            inversion[seq_length - i - 1] = 'G';
        } else {
            inversion[seq_length - i - 1] = 'C';
        }
    }
    inversion[i] = '\0';
    return inversion;
}

void compare(char *protein, char *tmp, Code *tab, int k) {
    int i;

    for (i = 0; i < 64; i++) {
        if (strcmp(tmp, tab[i].codon) == 0) {
            protein[k] = tab[i].acid;
            return;
        }
    }
    protein[k] = '?';
}

void translate(Sequences *seq) {
    // Création du fichier de sortie pour la traduction
    FILE *fd;

    fd = fopen("data/translation.txt", "w");
    if (fd == NULL) {
        err(EXIT_FAILURE, "Erreur fopen: translation.txt:");
    }

    Code *tab = initialize();
    char tmp[4];

    while (seq != NULL) {
        char *sequence;
        int i, j = 0, k = 0;
        size_t a;

        if (isARN(seq->sequence) == 0) {
            char *ARN;
            // Trancription de la séquence ADN en ARN pour ensuite la traduire
            ARN = strdup(transcription(seq->sequence));

            sequence = strstr(ARN, "AUG");
        } else {
            // Recherche du codon initiateur et renvoie la séquence à traduire
            sequence = strstr(seq->sequence, "AUG");
        }

        if (sequence != NULL) {
            char *protein = (char *)malloc(1);
            do {
                for (i = 0; i < 3; i++) {                   // On récupère le codon de la séquence
                    tmp[i] = sequence[j];
                    j++;
                }
                tmp[3] = '\0';
                compare(protein, tmp, tab, k);
                protein = (char *)realloc(protein, k + 2);

                // Si le codon est STOP , représenté par *, on arrête de traduire la séquence
                if (protein[k] == '*') {
                    break;
                }
                k++;
            } while (sequence[j] == 'A' || sequence[j] == 'C' || sequence[j] == 'G' || sequence[j] == 'U');      // Tant que la séquence n'est pas finie

            // Commentaire suivant si la séquence a pu être traduite entièrement ou si un codon STOP est au milieu de la séquence
            if (sequence[j] == 'A' || sequence[j] == 'C' || sequence[j] == 'G' || sequence[j] == 'U') {
                fprintf(fd, "Traduction du gène %s : \n", seq->name);
                fprintf(fd, "Attention, le codon STOP est prématuré\n");
            } else if (protein[k] != '*') {
                fprintf(fd, "Traduction du gène %s : \n", seq->name);
                fprintf(fd, "Attention, il n'y a pas de codon STOP\n");
            } else {
                fprintf(fd, "Traduction du gène %s : \n", seq->name);
            }
            for (a = 0; a < strlen(protein); a++) {
                if (a % PROT_LINE_SIZE == 0 && a != 0) {
                    fputs("\n", fd);
                }
                fputc(protein[a], fd);
            }
            fputs("\n\n", fd);
            free(protein);
        }
        seq = seq->next;
        free(sequence);
    }
    fclose(fd);
    free(tab);
}
