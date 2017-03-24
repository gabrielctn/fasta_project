#ifndef SEARCH_H
#define SEARCH_H

#include "sequences.h"
#include <stdint.h>



bool searchByGeneName(Sequences *s, char *geneName, int occ);
int searchBySequence(Sequences *seq, int occ, char *search);
int searchByPosition(Sequences *seq, int occ, int position, enum chromosome_t chromosome);
void searchBySubSequence(Sequences *seq, int occ, char *sequence);

#endif
