#include "headers/global.h"
#include "headers/search.h"
#include "headers/start.h"
#include "headers/dictionary.h"


int main(int argc, char *argv[]) {

	// Allocation de la structure contenant les variables du menu
	Menu *m = (Menu *) malloc(sizeof(Menu));
	Sequences *sequences;
	// Allocation du dictionnaire
	Nucleic_Dict *nd = (Nucleic_Dict *) malloc(sizeof(Nucleic_Dict));

	int nbPrefix;
	int choice;

	FILE *fd = fopen(FILENAME, "r");
	if(fd == NULL)
		err(EXIT_FAILURE,"Erreur fopen: %s:",FILENAME);

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
					printf("Désolé, aucune séquence correspondant ne se trouve dans le dictionnaire\n\n");
				break;
			case 6:
				printf("Recherche du nombre de séquences commençant par \"%s\" dans le dictionnaire\n\n", m->searchString);
				if((nbPrefix = searchNbPrefixDictionary(nd, m->searchString)))
					printf("Il y a %d séquences dont \"%s\" est le préfix\n\n", nbPrefix, m->searchString);
				else
					printf("Aucune séquence commence par \"%s\"\n\n", m->searchString);
				break;
			default:;
		}
	} while(choice != 7);

	printf("\n\nAu revoir cher bioinformaticien ...\n\n");

	/* FREE ALL */
	freeSeq(sequences);
	freeMenu(m);

	fclose(fd);

	return 0;
}
