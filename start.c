#include "headers/global.h"
#include "headers/sequences.h"
#include "headers/start.h"


void printMenu(){

	printf("\n\n\n********************** Manipulation de séquences nucléiques ou protéiques **********************\n\n");
	printf("1. Recherche par nom de gène\n");
	printf("2. Recherche par séquence donnée\n");
	printf("3. Recherche par position dans le génome\n");
	printf("4. Recherche de sous-séquence\n");
	printf("5. Recherche de séquence dans le dictionnaire\n");
	printf("6. Recherche de séquences par préfixe dans le dictionnaire\n");
	printf("7. Quitter\n");
}



void display_usage(){

	printf("\n\n********** USAGE **********\n\n");
	printf("./projet [-h] or [-n] or [-p]\n\n");

	printf("  -h	Print this help and exit\n");
	printf("  -n	The FASTA file contains nucleotide sequences\n");
	printf("  -p	The FASTA file contains proteic sequences\n");

	exit(EXIT_FAILURE);
}



void parseCommandLine(int argc, char *argv[], Options *args){

	char opt;
	int i;

	if(argc != 2)
		display_usage();

	while((opt = getopt(argc, argv, "hnp")) != -1){
		switch(opt){
			case 'h':
				display_usage();
			case 'n':
				args->nucleic = TRUE;
				break;
			case 'p':
				args->proteic = TRUE;
				break;
			default: abort();
		}
	}

	for(i=optind; i<argc; i++)
		printf("Non-option argument %s\n", argv[i]);
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
	} while(choice < 1 && choice > 7);

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
			printf("Entrez la séquence en 1 seule ligne, sans retours à la ligne (2000 caractères max): ");
			scanf("%s",dicoSearchSeq);
			m->searchString = strdup(dicoSearchSeq);
			break;
		case 6:
			printf("Entrez le préfixe (100 caractères max): ");
			scanf("%s",dicoPrefixSearch);
			m->searchString = strdup(dicoPrefixSearch);
			break;
		default:;
	}
	printf("\n\n");

	return choice;
}
