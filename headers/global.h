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
#define EXIT_FAILURE 1

typedef enum { FALSE, TRUE } bool;

#endif
