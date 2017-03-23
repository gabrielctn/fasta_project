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



void translate(Sequences *seq){
    char tmp[4];
    Code *tab= initialize();
    printf("%s\n", tab[0].codon);
    while(seq!=NULL){
        char *sequence;
        int i,j=0,k=0;

        sequence=strstr(seq->sequence,"ATG");       // Recherche du codon initiateur et renvoie la séquence à traduire
        if(sequence!=NULL){
            char *protein = (char *)malloc(1);
            do{
                for(i=0;i<3;i++){                    //On récupère le codon de la séquence
                    tmp[i]=sequence[j++];
                }
                tmp[3]='\0';
                compare(protein,tmp,tab,k);
                protein=(char *)realloc(protein,k+2);

                // Si le codon est STOP on arrête de traduire la séquence
                if(protein[k]=='Z'){
                    protein[k]='\0';
                    break;
                }
                k++;
            }while(sequence[j]=='A' ||sequence[j]=='C' ||sequence[j]=='G' ||sequence[j]=='T');      // Tant que la séquence n'est pas finie

            // Commentaire suivant si la séquence a pu être traduite entièrement ou si un codon STOP est au milieu de la séquence
            if(sequence[j]=='A' ||sequence[j]=='C' ||sequence[j]=='G' ||sequence[j]=='T'){
                printf("Attention, le codon STOP est prématuré");
                printf("Traduction du gène %s : \n %s\n", seq->name, protein);
            }else if(protein[k]!='Z'){
                printf("Attention, il n'y a pas de codon STOP  ");
                printf("Traduction du gène %s : \n %s\n", seq->name, protein);
            }else{
                printf("Traduction du gène %s : \n %s\n", seq->name, protein);
            }
        }
        seq=seq->next;
    }
}
