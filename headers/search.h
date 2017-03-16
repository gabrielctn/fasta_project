#ifndef SEARCH_H
#define SEARCH_H

#include "sequences.h"
#include <stdint.h>



bool searchByGeneName(Sequences *s, char *geneName, uint32_t occ);
int searchBySequence(Sequences *seq, uint32_t occ, char *search);
int searchByPosition(Sequences *seq, uint32_t occ, uint32_t position, enum chromosome_t chromosome);


#endif
