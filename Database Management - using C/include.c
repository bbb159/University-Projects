#include "include.h"



void escrever_no_disco(FILE**pfile,char*str){
*pfile = fopen("blocos.txt","w");

fprintf(*pfile,str,str);

*pfile = fclose(*pfile);

}



void ler_do_disco(FILE**pfile,char*k){
*pfile = fopen("blocos.txt","r");

int x = 0;


//fseek(*pfile,x,SEEK_CUR);
int i;
for(i=0;i<6;i++){
fscanf(*pfile,"%c",&k[i]);
printf("%d %c",i,k[i]);
}

*pfile = fclose(*pfile);

}
