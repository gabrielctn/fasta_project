#include "headers/global.h"
#include "headers/search.h"
#include "headers/sequences.h"
#include "headers/start.h"


int main(int argc, char *argv[]) {

	struct arg *args = (struct arg *) malloc(sizeof(struct arg));
	Seq *sequences;

	/* Récupère les options de la ligne de commande et initialise la structure arguments */
	parseCommandLine(argc, argv, args);

	FILE *fd = fopen(FILENAME, "r");
	if(fd == NULL)
		err(EXIT_FAILURE,"Erreur fopen: %s:",FILENAME);

	/* Lit le fichier FASTA et rempli la structure séquences */
	sequences = readSeq(fd);

	/* Recherche parmis les séquences du fichier FASTA celles qui match le nom de gène donné en argument */
	searchByGeneName(sequences, args->search, args->occ);

	/* FREE ALL */
	freeSeq(sequences);
	freeArg(args);

	fclose(fd);

	return 0;
}
