#include "headers/global.h"
#include "headers/search.h"
#include "headers/start.h"
#include "headers/dictionary.h"
#include "headers/translate.h"


int main(int argc, char *argv[]) {

	// Allocation des arguments en ligne de commande
	Options *args = (Options *) malloc(sizeof(Options));
	args->nucleic = FALSE;
	args->proteic = FALSE;
	parseCommandLine(argc, argv, args);

	// Allocation de la structure contenant les variables du menu
	Menu *m = (Menu *) malloc(sizeof(Menu));
	Sequences *sequences;

	// Allocation du dictionnaire
	Nucleic_Dict *nd = (Nucleic_Dict *) malloc(sizeof(Nucleic_Dict));

	int nbPrefix;
	int choice;

	FILE *fd = openFile(args);

	/* Lit le fichier FASTA et rempli la structure séquences */
	sequences = readSeq(fd);
	initNucleicDictionary(nd, sequences);

	/* Affiche le menu et initialise la structure des variables du menu données par l'utilisateur */
	system("clear");
	do{
		choice = menu(m);
		switch(choice){
			case 1:
				searchByGeneName(sequences, m->searchString, m->occ);
				break;
			case 2:
				searchBySequence(sequences, m->occ, m->searchString);
				break;
			case 3:
				searchByPosition(sequences, m->occ, m->position, m->chromosome);
				break;
			case 4:
				searchBySubSequence(sequences, m->occ, m->searchString);
				break;
			case 5:
				printf("Recherche de la séquence \"%s\" dans le dictionnaire\n\n", m->searchString);
				if(searchSeqDictionary(nd, m->searchString))
					printf("Trouvé ! La séquence se trouve dans le dictionnaire\n\n");
				else
					printf("Désolé, aucune séquence correspondante ne se trouve dans le dictionnaire\n\n");
				break;
			case 6:
				printf("Recherche du nombre de séquences commençant par \"%s\" dans le dictionnaire\n\n", m->searchString);
				if((nbPrefix = searchNbPrefixDictionary(nd, m->searchString)))
					printf("Il y a %d séquences dont \"%s\" est le préfix\n\n", nbPrefix, m->searchString);
				else
					printf("Aucune séquence commence par \"%s\"\n\n", m->searchString);
				break;
			case 7:
				if(args->nucleic == TRUE)
					translate(sequences);
				else
					printf("Fichier non nucléique, impossible de traduire\n");
				break;
			default:;
		}
	} while(choice != 8);

	system("clear");
	printf("\nAu revoir cher bioinformaticien ...\n\n");

	/* FREE ALL */
	freeSeq(sequences);
	freeMenu(m);
	freeOpt(args);

	fclose(fd);

	return 0;
}
