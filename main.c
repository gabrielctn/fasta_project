#include "headers/global.h"
#include "headers/search.h"
#include "headers/sequences.h"
#include "headers/start.h"


int main(int argc, char *argv[]) {

	Menu *m = NULL;
	Sequences *sequences;

	FILE *fd = fopen(FILENAME, "r");
	if(fd == NULL)
		err(EXIT_FAILURE,"Erreur fopen: %s:",FILENAME);

	/* Lit le fichier FASTA et rempli la structure séquences */
	sequences = readSeq(fd);

	/* Affiche le menu et initialise la structure des variables du menu données par l'utilisateur */
	m = menu();

	if(m->geneName)
		searchByGeneName(sequences, m->geneName, m->occ);

	if(m->position)
		searchByPosition(sequences, m->occ, m->position, m->chromosome);


	/* FREE ALL */
	freeSeq(sequences);
	freeMenu(m);

	fclose(fd);

	return 0;
}
