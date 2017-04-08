#ifndef START_H
#define START_H

typedef struct menu {
    char codingSeq;
    char *searchString;     // chaîne de caractères utilisée pour les recherches dans la base ou dictionnaire
    enum chromosome_t chromosome;     // nom du chromosome pour compléter la recherche par position
    int position;     // recherche de séquences par position dans le génome
    int occ;     // nombre d'occurences des séquences à afficher
    int transl;     // valeur pour choix de traduction
} Menu;

typedef struct args {
    bool nucleic;
    char *nuclFile;
    bool proteic;
    char *protFile;
} Options;

void printMenu();
int menu(Menu *m);
void freeMenu(Menu *m);
void freeOpt(Options *args);
void display_usage();
void parseCommandLine(int argc, char *argv[], Options *args);
FILE *openFile(Options *args);
void setTerminalMode(int mode);
char *getSring();

#endif
