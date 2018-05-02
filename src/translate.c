#include "../headers/translate.h"
#include "../headers/global.h"

/* Initialize la structure du code génétique à partir du fichier
 * contenant le code génétique */
Code *initialize() {
    int i;
    Code *tab = (Code *)calloc(64, sizeof(Code));
    if (NULL == tab) {
        err(EXIT_FAILURE, "Erreur avec calloc de Code\n");
    }
    FILE *fd = fopen("data/codegenetic.txt", "r");

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
    if (strstr(sequence, "U") == NULL) { // Si on a trouvé un U dans la séquence,
        return 0;                        // on a une séquence d'ARN, on peut donc traduire directement
    }
    return 1;
}

char *transcription(char *sequence) {
    size_t seqLength, i;

    seqLength = strlen(sequence);
    char *reverse = (char *)calloc(seqLength + 1, sizeof(char));
    if (NULL == reverse) {
        err(EXIT_FAILURE, "Erreur avec calloc de reverse\n");
    }
    // Transcription: l'ADN est transformé en ARN pour pouvoir être traduite
    // Les T deviennent des A et les C des G et inversement
    for (i = 0; i < seqLength; i++) {
        if (sequence[i] == 'A') {
            reverse[seqLength - i - 1] = 'U';
        } else if (sequence[i] == 'T') {
            reverse[seqLength - i - 1] = 'A';
        } else if (sequence[i] == 'C') {
            reverse[seqLength - i - 1] = 'G';
        } else {
            reverse[seqLength - i - 1] = 'C';
        }
    }
    reverse[i] = '\0';
    return reverse;
}

// Compare le codon analysé au code génétique
void compare(char *protein, char *tmp, Code *tab, int prot_idx) {
    int i;

    for (i = 0; i < 64; i++) {
        if (strcmp(tmp, tab[i].codon) == 0) {
            protein[prot_idx] = tab[i].acid;
            return;
        }
    }
    protein[prot_idx] = '?';
}

int isNucleotide(char nucl) {
    return nucl == 'A' || nucl == 'C' || nucl == 'G' || nucl == 'U' || nucl == 'T';
}

// Ecrit la séquence traduite avec des commentaires dans le fichier "data/translation.txt"
void printing(char *sequence, int seq_idx, char *protein, int prot_idx, char *name, FILE *fd) {
    size_t a;

    // Commentaire suivant si la séquence a pu être traduite entièrement ou si un codon STOP est au milieu de la séquence
    fprintf(fd, "Traduction du gène %s : \n", name);
    if (isNucleotide(sequence[seq_idx])) {
        fprintf(fd, "Attention, le codon STOP est prématuré\n");
    } else if (protein[prot_idx] != '*') {
        fprintf(fd, "Attention, il n'y a pas de codon STOP\n");
    }
    // Ecrit la séquence
    for (a = 0; a < strlen(protein); a++) {
        if (a % PROT_LINE_SIZE == 0 && a != 0) {
            fputs("\n", fd);
        }
        fputc(protein[a], fd);
    }
    fputs("\n\n", fd);
}

char *sequenceToTranslate(Sequences *seq, Menu *m, char *ARNm) {
    char *sequence;

    if (m->codingSeq == 'n' && isARN(seq->sequence) == 0) {
        // Trancription de la séquence ADN en ARN pour ensuite la traduire
        ARNm = transcription(seq->sequence);
        sequence = strstr(ARNm, "AUG");
    } else {
        char *codon = (m->codingSeq == 'o') ? "ATG" : "AUG";
        // Recherche le codon initiateur et renvoie la séquence à traduire
        sequence = strstr(seq->sequence, codon);
    }
    return sequence;
}

void verbose(Menu *m) {
    if (m->occ == 0) {
        printf("\nTraduction de toutes les séquences du fichier FASTA\n\n");
    } else if (m->occ == 1) {
        printf("\nTraduction de la première séquence du fichier FASTA\n\n");
    } else {
        printf("\nTraduction des %d premières séquences du fichier FASTA\n\n", m->occ);
    }
}

/* Traduit une séquence nucléotidique en séquence protéique.
 * Prend en compte si c'est une séquence codante ou non. */
char *synthetizeProtein(int seq_idx, int prot_idx, char *sequence, Code *tab) {
    int i;
    char tmp[4];
    char *protein = (char *)calloc(2, sizeof(char));

    if (NULL == protein) {
        err(EXIT_FAILURE, "Erreur avec calloc de protein\n");
    }

    do {
        // On récupère le codon de la séquence
        for (i = 0; i < 3 && isNucleotide(sequence[seq_idx]); i++) {
            /* Si la séquence donnée est codante, on traduit directement de l'ADN,
             * il faut donc changer les T en U pour la lecture des codons dans le code génétique */
            tmp[i] = (sequence[seq_idx] == 'T') ? 'U' : sequence[seq_idx];
            seq_idx++;
        }

        tmp[i] = '\0';
        compare(protein, tmp, tab, prot_idx);
        // Si c'est un codon STOP, représenté par *, on arrête de traduire la séquence
        if (protein[prot_idx] == '*') {
            protein[prot_idx + 1] = '\0';
            return protein;
        }
        char *tmpProtein = (char *)realloc(protein, prot_idx + 3);
        if (NULL == tmpProtein) {
            err(EXIT_FAILURE, "Erreur realloc protein\n");
        } else {
            protein = tmpProtein;
        }
        prot_idx++;
    } while (isNucleotide(sequence[seq_idx]));/* Tant que la séquence n'est pas finie,
                                               * il existe des bases nucléotidiques */
    // En sortant ici, il n'y a pas eu de codon stop, donc d'*
    if (sequence[seq_idx] == 'N') {
        err(EXIT_FAILURE, " Erreur: rencontre du nucléotide N, acide nucléique masqué. Impossible de traduire\n");
    }
    protein[prot_idx] = '\0';

    return protein;
}

void translate(Sequences *seq, Menu *m) {
    // Création du fichier de sortie pour la traduction
    FILE *fd = NULL;
    int nbOcc = 0;

    fd = fopen("data/translation.txt", "w");

    if (fd == NULL) {
        err(EXIT_FAILURE, "Erreur fopen: translation.txt:");
    }

    Code *tab = initialize();
    verbose(m);

    while (seq != NULL) {
        char *ARNm = NULL;
        int seq_idx = 0, prot_idx = 0;

        char *sequence = sequenceToTranslate(seq, m, ARNm);
        if (sequence != NULL) { // Si on a bien trouvé un codon initiateur
            char *protein = synthetizeProtein(seq_idx, prot_idx, sequence, tab);
            // printf("%s\n", protein);
            printing(sequence, seq_idx, protein, prot_idx, seq->name, fd);
            free(protein);
        }
        if (m->codingSeq == 'n') {
            free(ARNm);
        }
        seq = seq->next;
        ++nbOcc;
        if (nbOcc == m->occ) {
            break;
        }
    }
    printf("Les séquences ont bien été traduites!\n\n");

    fclose(fd);
    free(tab);
}
