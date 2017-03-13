#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "global.h"

// Style: encore une fois, pas la peine d'être avare en
// caractères. 'Sequence', c'est pas beaucoup plus la mort à taper que
// 'Seq' (et avec un bon éditeur, tu ne devrais même pas avoir à taper
// un mot entier mais utiliser l'auto-complétion ;) )
void printSeq(Seq *s);
void printAllSeq(Seq *s);
enum chromosome_t conversionEnum(char * chr);
void freeSeq(Seq *s);
void parseHeader(FILE *fd, Seq *seq);
void getSeq(FILE *fd, Seq *seq, char *singleLine);
Seq * readSeq(FILE *fd);





#endif
