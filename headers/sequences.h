#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "global.h"


void printSeq(Sequences *s);
void printAllSeq(Sequences *s);
enum chromosome_t str2enum(char * chr);
void freeSeq(Sequences *s);
void parseHeader(FILE *fd, Sequences *seq);
void getSeq(FILE *fd, Sequences *seq, char *singleLine);
Sequences * readSeq(FILE *fd);


#endif
