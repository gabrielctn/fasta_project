#ifndef START_H
#define START_H

typedef struct args {
    bool nucleic;
    bool proteic;
    bool translate;
    char *codingSeq;
    char *file;
    char *gene;
    char *sequence;
    char *subSequence;
    char *dictSequence;
    char *dictPrefix;
    int position;     // recherche de séquences par position dans le génome
    int occ;     // nombre d'occurences des séquences à afficher
    enum chromosome_t chromosome;     // nom du chromosome pour compléter la recherche par position
} Options;

void freeOpt(Options *args);
void displayUsage();
void getOptions(int argc, char *argv[], Options *args);
void checkArgs(Options *args);
FILE *openFile(Options *args);

#endif
