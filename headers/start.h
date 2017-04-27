#ifndef START_H
#define START_H

enum chromosome_t {I, II, III, MT, MTR, AB325691};

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
    bool assembly;
    char *assembleFile;
} Options;

void printMenu();
int menu(Menu *m, Options *args);
void freeMenu(Menu *m);
void freeOpt(Options *args);
void displayUsage();
void parseCommandLine(int argc, char *argv[], Options *args);
FILE *openFile(Options *args);
void setTerminalMode(int mode);
char *getSring();

#endif
