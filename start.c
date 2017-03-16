#include "headers/global.h"
#include "headers/sequences.h"


void display_usage(){

	printf("\n\n********** USAGE **********\n\n");
	printf("./projet [-h] [-n OCCURENCES] [-d STRING] [-r STRING] [-t NB_GENES]\n\n");

	printf("  -h					print this help and exit\n");
	printf("  -n OCCURENCES			set number of occurences to print. VALUES: 0 (all) 1 (first) >1 (n first) DEFAULT is all\n");
	printf("  -d STRING				string used for search or insertion in dictionnary\n");
	printf("  -r STRING				string (gene name, sequence etc.) used for searching in the file\n");
	printf("  -t NB_GENES			set number of genes to translate\n\n");

	exit(EXIT_FAILURE);
}



void printMenu(){

	system("clear");
	printf("********************** Manipulation de séquences nucléiques ou protéiques **********************\n\n");
	printf("1. Recherche par nom de gène\n");
	printf("2. Recherche par séquence donnée\n");
	printf("3. Recherche par position dans le génome\n");
	printf("4. Recherche de sous-séquence\n");
}



void freeMenu(Menu *m){

	free(m->searchDico);
	free(m->geneName);
	free(m->subSequence);
	free(m);
}


Menu * menu(){

	Menu * m = (Menu *) malloc(sizeof(Menu));
	uint32_t choice;
	char geneName[MAX_LENGTH_GENE_NAME];
	char subSequence[MAX_LENGTH_SUB_SEQUENCE];
	char chromosome[MAX_LENGTH_CHROMOSOME];

	printMenu();
	printf("\n\nQue voulez-vous faire ? : ");
	scanf("%u", &choice);

	switch(choice){
		case 1:
			printf("Entrez le nom du gène: ");
			scanf("%s",geneName);
			m->geneName = strdup(geneName);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%u",&(m->occ));
			break;
		case 2:
			printf("Entrez la séquence (100 caractères max): ");
			scanf("%s",subSequence);
			m->subSequence = strdup(subSequence);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%u",&(m->occ));
			break;
		case 3:
			printf("Entrez la position: ");
			scanf("%u", &(m->position));
			printf("Entrez le chromosome dans lequel il est supposé être trouvé: ");
			scanf("%s",chromosome);
			m->chromosome = str2enum(chromosome);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%u",&(m->occ));
			break;
		default:;
	}
	printf("\n\n");

	return m;
}
