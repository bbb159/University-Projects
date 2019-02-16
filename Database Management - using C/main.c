#include "include.h"
#include "ged.h"
#include "ga.h"
#include "gbp.h"

int main()
{

FILE*pfile;
printf("Registro a ser inserido: ");
char w[7],r[6];
gets(&w);

escrever_no_disco(&pfile,w);

ler_do_disco(&pfile,r);

printf("%s",r);

ged g_disco;
gbp g_bufferpool;

 /*
pfile = fclose(pfile);

Precisamos implementar
- inicializar a memoria como um array
- inicializar sgbd = (GBP GA E GED)*malloc
- alocar tabela (nome,malloc, alterar o GED e o GA)
- escrever dado na tabela (inicialmente uma string)
- solicita diretorio arquivo

- apagar dado na tabela
- atualizar dado da tabela
- consultar dado na tabela
- desalocar tabela
- politicas de substituição ( LRU)
- gravar dados e sair
*/



}
