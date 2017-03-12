#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "global.h"


void printSeq(Seq *s);
void printAllSeq(Seq *s);
enum chromosome_t conversionEnum(char * chr);
void freeSeq(Seq *s);
void parseHeader(FILE *fd, Seq *seq);
void getSeq(FILE *fd, Seq *seq, char *singleLine);
Seq * readSeq(FILE *fd);





#endif
