#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "global.h"

#define DESCRIPTION_SIZE 154
#define HEADER_SIZE 274
#define SEQ_LINE_SIZE 60


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


void printSeq(Sequences *s);
void printAllSeq(Sequences *s);
enum chromosome_t str2enum(char * chr);
void freeSeq(Sequences *s);
void parseHeader(FILE *fd, Sequences *seq);
void getSeq(FILE *fd, Sequences *seq, char *singleLine);
Sequences * readSeq(FILE *fd);
long totalLengthSequences(Sequences *seq);


#endif
