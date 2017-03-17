#include "headers/global.h"
#include "headers/sequences.h"
#include "headers/start.h"

void display_usage(){

	printf("\n\n********** USAGE **********\n\n");
	printf("./projet [-h] [-n OCCURENCES] [-d STRING] [-r STRING] [-t NB_GENES]\n\n");

	printf("  -h					print this help and exit\n");
	printf("  -n OCCURENCES			set number of occurences to print. VALUES: 0 (all) 1 (first) >1 (n first) DEFAULT is all\n");
	printf("  -d STRING				string used for search or insertion in dictionary\n");
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
	printf("5. Recherche de séquence dans le dictionnaire\n");
	printf("6. Recherche de séquences par préfixe dans le dictionnaire\n");
}



void freeMenu(Menu *m){

	free(m->searchString);
	free(m);
}


int menu(Menu *m){

	int choice;
	char geneName[MAX_LENGTH_GENE_NAME];
	char searchSequence[MAX_LENGTH_SEARCH_SEQUENCE];
	char chromosome[MAX_LENGTH_CHROMOSOME];
	char subSequence[MAX_LENGTH_SUB_SEQUENCE];
	char dicoSearchSeq[MAX_LENGTH_DICO_SEARCH_SEQUENCE];
	char dicoPrefixSearch[MAX_LENGTH_DICO_PREFIX_SEARCH];

	printMenu();
	do{
		printf("\n\nQue voulez-vous faire ? : ");
		scanf("%d", &choice);
	} while(choice < 1 && choice > 6);

	switch(choice){
		case 1:
			printf("Entrez le nom du gène: ");
			scanf("%s",geneName);
			m->searchString = strdup(geneName);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%d",&(m->occ));
			break;
		case 2:
			printf("Entrez la séquence (100 caractères max): ");
			scanf("%s",searchSequence);
			m->searchString = strdup(searchSequence);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%d",&(m->occ));
			break;
		case 3:
			printf("Entrez la position: ");
			scanf("%d", &(m->position));
			printf("Entrez le chromosome dans lequel il est supposé être trouvé: ");
			scanf("%s",chromosome);
			m->chromosome = str2enum(chromosome);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%d",&(m->occ));
			break;
		case 4:
			printf("Entrez la séquence (100 caractères max): ");
			scanf("%s",subSequence);
			m->searchString = strdup(subSequence);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%d",&(m->occ));
			break;
		case 5:
			printf("Entrez la séquence (500 caractères max): ");
			scanf("%s",dicoSearchSeq);
			m->searchString = strdup(dicoSearchSeq);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%d",&(m->occ));
			break;
		case 6:
			printf("Entrez le préfixe (100 caractères max): ");
			scanf("%s",dicoPrefixSearch);
			m->searchString = strdup(dicoPrefixSearch);
			printf("Entrez le nombre d'occurences accepté, toutes (0), 1 ou n : ");
			scanf("%d",&(m->occ));
			break;
		default:;
	}
	printf("\n\n");

	return choice;
}
