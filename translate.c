#include "headers/translate.h"
#include "headers/global.h"

Code *initialize()
{
    int i;
    Code *tab = (Code *)calloc(64, sizeof(Code));
    FILE *fd  = fopen("codegenetic.txt", "r");

    if (fd == NULL) {
        err(EXIT_FAILURE, "Erreur fopen: codegenetic.txt:");
    }

    for (i = 0; i < 64; i++) {
        fscanf(fd, "%c %s\n", &(tab[i].acid), tab[i].codon);
    }
    return tab;
}

void compare(char *protein, char *tmp, Code *tab, int k)
{
    int i;

    for (i = 0; i < 64; i++) {
        if (strcmp(tmp, tab[i].codon) == 0) {
            protein[k] = tab[i].acid;
            return;
        }
    }
    protein[k] = '?';
}

void translate(Sequences *seq)
{
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

        sequence = strstr(seq->sequence, "ATG");       // Recherche du codon initiateur et renvoie la séquence à traduire
        if (sequence != NULL) {
            char *protein = (char *)malloc(1);
            do {
                for (i = 0; i < 3; i++) {                   // On récupère le codon de la séquence
                    // Pour les ARNm le T est remplacé par un U mais il a les même propriétés que le T, on remplace donc le U par le T pour faciliter la traduction
                    if (sequence[j] == 'U') {
                        tmp[i] = 'T';
                    }
                    tmp[i] = sequence[j];
                    j++;
                }
                tmp[3] = '\0';
                compare(protein, tmp, tab, k);
                protein = (char *)realloc(protein, k + 2);

                // Si le codon est STOP on arrête de traduire la séquence
                if (protein[k] == 'Z') {
                    break;
                }
                k++;
            } while (sequence[j] == 'A' || sequence[j] == 'C' || sequence[j] == 'G' || sequence[j] == 'T');      // Tant que la séquence n'est pas finie

            // Commentaire suivant si la séquence a pu être traduite entièrement ou si un codon STOP est au milieu de la séquence
            if (sequence[j] == 'A' || sequence[j] == 'C' || sequence[j] == 'G' || sequence[j] == 'T') {
                fprintf(fd, "Traduction du gène %s : \n", seq->name);
                fprintf(fd, "Attention, le codon STOP est prématuré\n");
            } else if (protein[k] != 'Z') {
                fprintf(fd, "Traduction du gène %s : \n", seq->name);
                fprintf(fd, "Attention, il n'y a pas de codon STOP\n");
            } else {
                protein[k] = '\0';
                fprintf(fd, "Traduction du gène %s : \n", seq->name);
            }
            for (a = 0; a < strlen(protein); a++) {
                if (a % PROT_LINE_SIZE == 0 && a != 0) {
                    fputs("\n", fd);
                }
                fputc(protein[a], fd);
            }
            fputs("\n\n", fd);
        }
        seq = seq->next;
    }
    fclose(fd);
}
