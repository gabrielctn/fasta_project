// Style: Ne match pas le nom du fichier.
#ifndef RECHERCHE_H
#define RECHERCHE_H

// Style: les includes 'système' en premier, puis les tiens.
#include "sequences.h"
#include <stdint.h>

// Style: inutile de mettre autant de lignes blanches.

// Pourquoi un booléen? Imagine: "Je cherche cette séquence svp?"
// "Oui"...  Perso, je m'attends à ce qu'on me retourne peut-être
// l'emplacement de la séquence, ou alors les emplacements s'il y en a
// plusieurs, ou bien un pointeur, ou une liste des occurrences...
bool searchByGeneName(Seq *s, char *geneName, uint32_t occ);


#endif
