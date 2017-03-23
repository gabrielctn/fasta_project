#include "headers/translate.h"
#include "headers/global.h"



Code * initialize(){
    int i;
    Code *tab=(Code *)calloc(64,sizeof(Code));
    FILE *fd = fopen("codegenetic.txt", "r");
	if(fd == NULL)
		err(EXIT_FAILURE,"Erreur fopen: codegenetic.txt:");

    for(i=0;i<64;i++){
        fscanf(fd,"%c %s\n",&(tab[i].acid), tab[i].codon);
    }
    return tab;
}





void compare(char *protein, char *tmp, Code *tab, int k){
    int i;
    for(i=0;i<64;i++){
        if(strcmp(tmp,tab[i].codon)==0){
            protein[k]=tab[i].acid;
            return;
        }
    }
    protein[k]='?';
}
