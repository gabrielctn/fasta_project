#ifndef START_H
#define START_H

#define MAX_LENGTH_GENE_NAME 20
#define MAX_LENGTH_SEARCH_SEQUENCE 100
#define MAX_LENGTH_SUB_SEQUENCE 50
#define MAX_LENGTH_CHROMOSOME 10
#define MAX_LENGTH_DICO_SEARCH_SEQUENCE 2000
#define MAX_LENGTH_DICO_PREFIX_SEARCH 50


typedef struct menu {
	char *searchString; // chaîne de caractères utilisée pour les recherches dans la base ou dictionnaire
	enum chromosome_t chromosome; // nom du chromosome pour compléter la recherche par position
	int position; // recherche de séquences par position dans le génome
	int occ; // nombre d'occurences des séquences à afficher
	int transl; // valeur pour choix de traduction
} Menu;


void printMenu();
int menu(Menu *m);
void freeMenu(Menu *m);

#endif
