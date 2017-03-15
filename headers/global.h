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
#define DESC_SIZE 154
#define HEADER_SIZE 274
#define SEQ_LINE_SIZE 60
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


typedef struct options {
	char *searchDico; // séquence à rechercher dans le dico
	char *search; // chaine à rechercher dans les séquences
	uint32_t occ; // nombre d'occurences
	uint32_t transl; // valeur pour choix de traduction
} Options;

#endif
