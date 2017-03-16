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
#define DEBUG_SEQUENCES 0 // Si vaut 1, la sortie peut être longue car affiche toutes les séquences fasta
#define DEBUG_SEARCH 1
#define DESCRIPTION_SIZE 154
#define HEADER_SIZE 274
#define SEQ_LINE_SIZE 60
#define MAX_LENGTH_GENE_NAME 20
#define MAX_LENGTH_SEARCH_SEQUENCE 100
#define MAX_LENGTH_SUB_SEQUENCE 100
#define MAX_LENGTH_CHROMOSOME 10
#define EXIT_FAILURE 1


typedef enum { FALSE, TRUE } bool;

enum chromosome_t {I, II, III, MT, MTR, AB325691};

typedef struct sequences {
	char name[17]; // le nom de la sequence sans le '>' initial, termine par '\0'
	enum chromosome_t chromosome;
	int start; // numero de base de debut
	int end; // et de fin
	char *description; // copie de la chaine "description"
	char *sequence;    // toute la sequence sur {A,C,G,T}  sans '\n' terminee par '\0'
	struct sequences *next;  // pour faire une liste chainee. NULL si dernier.
} Sequences;


typedef struct menu {
	char *searchDico; // séquence à rechercher dans le dico
	char *geneName; // nom du gène à rechercher dans les séquences
	char *searchSequence; // séquence donnée pour la recherche
	char *subSequence; // pour la recherche par sous séquence
	enum chromosome_t chromosome; // nom du chromosome pour compléter la recherche par position
	int position; // recherche de séquences par position dans le génome
	int occ; // nombre d'occurences des séquences à afficher
	int transl; // valeur pour choix de traduction
} Menu;


#endif
