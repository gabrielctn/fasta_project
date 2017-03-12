#include "headers/search.h"
#include "headers/global.h"

bool searchByGeneName(Seq *s, char *geneName, uint32_t occ){

	bool found = FALSE;
	int i=0;

	while(s->suiv != NULL){
		// Affiche toutes les séquences correspondantes (occ = 0) ou juste la 1ère (occ = 1)
		if((occ == 0 || occ == 1) && strcmp(s->nom, geneName) == 0){
			printSeq(s);
			found = TRUE;
			if(occ == 1) return found;
		}
		// Affiche les n séquences correspondantes
		if((occ > 1) && (strcmp(s->nom, geneName) == 0) && (i++ < occ)){
				printSeq(s);
				found = TRUE;
		}
		s = s->suiv;
	}
	return found;
}
