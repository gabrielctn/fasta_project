#include "headers/sequences.h"

#define DEBUG_SEQUENCES 0 // Si vaut 1, la sortie peut être longue car affiche toutes les séquences fasta

/* Affichage d'une sequence */
void printSeq(Sequences *s) {
    char *chromoName[] = { "I", "II", "III", "MT", "MTR", "AB325691" };
    size_t size = s->end - s->start + 1;

    printf("%s %s[%i-%i] %s", s->name, chromoName[s->chromosome], s->start, s->end, s->description);
    if (strlen(s->sequence) != size) {
        printf(" tronquee a %li bases\n", strlen(s->sequence));
    } else {
        printf("\n");
    }
}

/* Affichage de toutes les sequences */
void printAllSeq(Sequences *s) {
    if (s != NULL) {
        printAllSeq(s->next);
        printSeq(s);
        /* inverser ces deux lignes pour afficher la liste a l'envers.
         * Utile si construite par ajouts en tete : on aura l'ordre
         * du fichier. */
    }
}

/*converti le type du chromosome dans sa valeur enum */
enum chromosome_t str2enum(char *chr) {
    enum chromosome_t chromosome;

    if (strcmp(chr, "I") == 0) {
        chromosome = I;
    }
    if (strcmp(chr, "II") == 0) {
        chromosome = II;
    }
    if (strcmp(chr, "III") == 0) {
        chromosome = III;
    }
    if (strcmp(chr, "MT") == 0) {
        chromosome = MT;
    }
    if (strcmp(chr, "MTR") == 0) {
        chromosome = MTR;
    }
    if (strcmp(chr, "AB325691") == 0) {
        chromosome = AB325691;
    }

    return chromosome;
}

/* Libère récursivement la liste chaînée */
void freeSeq(Sequences *s) {
    if (s == NULL) {
        return;
    } else {
        freeSeq(s->next);
        free(s->sequence);
        free(s->description);
        free(s);
    }
}

char *parseHeaderAssembleFile(FILE *fd) {
    char *str = (char *)calloc(HEADER_SIZE + 1, sizeof(char));
    fgets(str, HEADER_SIZE + 1, fd);    // récupère 1ère ligne
    return str;
}

/* Parse l'entête des séquences */
void parseHeader(FILE *fd, Sequences *seq) {
    int i;
    char str[HEADER_SIZE + 1], chromosome[40];

    fgets(str, HEADER_SIZE + 1, fd);    // récupère 1ère ligne

    for (i = 0; i < 5; i++) { // lit les 5 premiers champs de la 1ère ligne
        switch (i) {
        case 0:
            strcpy(seq->name, strtok(str, " "));                     // printf("%s",seq->sequence);Récupère le nom
            break;
        case 2:
            strcpy(chromosome, strtok(NULL, " "));                    // Récupère le champ chromosome pour le parser après
            break;
        default:
            strtok(NULL, " ");
        }
    }

    // parse l'entête
    strtok(NULL, "\"");
    seq->description = (char *)calloc(DESCRIPTION_SIZE + 1, sizeof(char));
    if (NULL == seq->description) {
        err(EXIT_FAILURE, "Erreur avec calloc de description\n");
    }
    strcpy(seq->description, strtok(NULL, "\""));

    // parse le champ "chromosome"
    strtok(chromosome, ":");
    strtok(NULL, ":");
    seq->chromosome = str2enum(strtok(NULL, ":"));    // type
    seq->start = atoi(strtok(NULL, ":"));    // debut
    seq->end = atoi(strtok(NULL, ":"));    // fin
    strtok(NULL, ":");
}

/* Récupère la séquence nucléotidique et l'enregistre dans la structure */
void getSeq(FILE *fd, Sequences *seq, char *singleLine) {
    char *newSeq;
    char c = (char)fgetc(fd);

    seq->sequence[0] = '\0';

    do {
        ungetc(c, fd);
        fgets(singleLine, SEQ_LINE_SIZE + 1, fd);
        c = (char)fgetc(fd);
        if (c != '\n') {
            ungetc(c, fd);                  // Enlève le retour à la ligne
        }
        newSeq = (char *)realloc(seq->sequence, strlen(seq->sequence) + strlen(singleLine) + 1);
        if (newSeq == NULL) {
            printf("\nError realloc\n");
            exit(EXIT_FAILURE);
        } else {
            seq->sequence = newSeq;
        }
        strcat(seq->sequence, singleLine);
        if (seq->sequence[strlen(seq->sequence) - 1] == '\n') {
            seq->sequence[strlen(seq->sequence) - 1] = '\0';
        }
        c = (char)fgetc(fd);         // Vérifie si la ligne suivante est un nouvel entête ou la suite de la séquence
    } while (c != '>' && !feof(fd));
    ungetc(c, fd);
}

/* Parse un fichier FASTA en allouant dynamiquement une liste chaînée */
Sequences *readSeq(FILE *fd, Options *args) {
    char c;
    char singleLine[SEQ_LINE_SIZE + 2];

    if (feof(fd)) {
        return NULL;              // Fin de fichier: fin de la liste chaînée
    }


    // Allocations dynamiques
    Sequences *seq = (Sequences *)calloc(1, sizeof(Sequences));
    if (NULL == seq) {
        err(EXIT_FAILURE, "Erreur avec calloc de Sequences\n");
    }
    seq->sequence = (char *)calloc(SEQ_LINE_SIZE + 1, sizeof(char));
    if (NULL == seq->sequence) {
        err(EXIT_FAILURE, "Erreur avec calloc de seq->sequence\n");
    }

    c = (char)fgetc(fd);
    if (c == '>') {
        if (args->assembly) {
            seq->assemblyHeader = strdup(parseHeaderAssembleFile(fd));
        } else {
            parseHeader(fd, seq);
        }
        if (DEBUG_SEQUENCES) {
            printf("Nom: %s\nChromosome: %d\ndebut: %d\nfin: %d\nDescription: %s\n", seq->name, seq->chromosome, seq->start, seq->end, seq->description);
        }
        getSeq(fd, seq, singleLine);
        if (DEBUG_SEQUENCES) {
            printf("%s\n", seq->sequence);
        }
    }
    seq->next = readSeq(fd, args);     // Appel récursif pour remplir la liste chaînée

    return seq;
}

long totalLengthSequences(Sequences *seq) {
    if (seq == NULL) {
        return 0;
    }
    return strlen(seq->sequence) + totalLengthSequences(seq->next);
}
