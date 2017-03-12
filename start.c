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



void freeArg(Arg *args){

	free(args->search);
	free(args->searchDico);
	free(args);
}



void parseCommandLine(int argc, char *argv[], struct arg *args){

	char opt;
	int i;

	while((opt = getopt(argc, argv, "hn:d:r:t:")) != -1){
		switch (opt){
			case 'h':
				display_usage();
			case 'n':
				args->occ = (uint32_t)atoi(optarg);
				break;
			case 'd':
				args->searchDico = (char *) malloc(strlen(optarg));
				args->searchDico = optarg;
				break;
			case 'r':
				args->search = (char *) malloc(strlen(optarg));
				args->search = optarg;
				break;
			case 't':
				args->transl = (uint32_t)atoi(optarg);
				break;
			case '?':
				display_usage();
				break;
			default: abort();
		}
	}
	if(DEBUG_SEARCH)
		printf("occ = %u, searchDico = %s, search = %s, transl = %u\n", args->occ, args->searchDico, args->search, args->transl);

	for(i=optind; i<argc; i++)
		printf("Non-option argument %s\n", argv[i]);
}
