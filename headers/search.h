#ifndef SEARCH_H
#define SEARCH_H

#include "sequences.h"
#include <stdint.h>



bool searchByGeneName(Sequences *s, char *geneName, uint32_t occ);
int search_sequence(Sequences *seq, uint32_t occ, char *search);

#endif
