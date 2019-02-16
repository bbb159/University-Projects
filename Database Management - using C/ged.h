#include "pagina.h"


typedef struct{
    //int id_pagina; //Qual pagina na memoria referencia esse bloco
    //int id_bloco; //Referencia ao bloco -> NÃO COLOCAMOS PORQUE CADA POSICAO DA ESTRUTURA ABAIXO CORRESPONDE AO DE CIMA
    int livre; //0 = CHEIO // 6 = 1 LIVRE // 12 = VAZIO
} bloco; //INFORMAÇÃO DE CADA BLOCO

typedef struct{
    bloco* blocos_disco; // VETOR PRA GUARDAR CADA BLOCO
    int controle;
} ged;



int inicializa_ged(int num_blocos); // Inicializa GED, alocando 'num_blocos' blocos

int aloca_bloco(void); //Criar um novo bloco e retornar o endereço do mesmo. ALOCAR SEMPRE UM BLOCO QUE TIVER LIVRE = 12

int desaloca_bloco(int id_bloco); //Responsável por desalocar um bloco

int escreve_bloco(pagina pagina); //Responsável por escrever página no bloco

pagina ler_bloco(int id_bloco); //Responsável por ler um bloco e retornar uma página correspondente. RECEBE ID DE UM BLOCO DA TABELA E RETORNA UMA PAGINA

