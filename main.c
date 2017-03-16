#include "headers/global.h"
#include "headers/search.h"
#include "headers/sequences.h"
#include "headers/start.h"
#include "headers/dictionary.h"


int main(int argc, char *argv[]) {

	Menu *m = NULL;
	Sequences *sequences;
	Nucleic_Dico *nd = (Nucleic_Dico *) malloc(sizeof(Nucleic_Dico));

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

	if(m->searchSequence)
		searchBySequence(sequences, m->occ, m->searchSequence);

	if(m->subSequence)
		searchBySsSequence(sequences, m->occ, m->subSequence);


	/* DICTIONNAIRE DE SEQUENCES */
	initNucleicDictionary(nd, sequences);


	if(searchDictionary(nd, "CAA"))
		printf("Trouvé !!\n\n");
	else
		printf("Pas trouvé !\n\n");

	/* FREE ALL */
	freeSeq(sequences);
	freeMenu(m);

	fclose(fd);

	return 0;
}
