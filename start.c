#include "headers/global.h"


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



void freeArg(Options *args){

	free(args->search);
	free(args->searchDico);
	free(args);
}
