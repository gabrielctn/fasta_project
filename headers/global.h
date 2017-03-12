#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <err.h>

#define FILENAME "data/S_pombe.fasta"
#define DEBUG_SEQUENCES 0
#define DEBUG_SEARCH 0
#define DESC_SIZE 154
#define HEADER_SIZE 274
#define SEQ_LINE_SIZE 60
#define SEARCH_STRING 20 // longueur max de la chaîne utilisée pour la recherche par nom
#define EXIT_FAILURE 1


typedef enum { FALSE, TRUE } bool;

enum chromosome_t {I, II, III, MT, MTR, AB325691};

typedef struct seq {
	char nom[17]; // le nom de la sequence sans le '>' initial, termine par '\0'
	enum chromosome_t chromosome;
	int deb; // numero de base de debut
	int fin; // et de fin
	char *description; // copie de la chaine "description"
	char *sequence;    // toute la sequence sur {A,C,G,T}  sans '\n' terminee par '\0'
	struct seq *suiv;  // pour faire une liste chainee. NULL si dernier.
} Seq;


typedef struct arg {
	char *searchDico; // séquence à rechercher dans le dico
	char *search; // chaine à rechercher dans les séquences
	uint32_t occ; // nombre d'occurences
	uint32_t transl; // valeur pour choix de traduction
} Arg;




#endif
