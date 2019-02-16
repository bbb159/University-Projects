#include "registro.h"

#define TAM_FRAME 2 //Cada frame conterá no máximo 2 slots

typedef struct {
    int id_pagina;
    registro slot[TAM_FRAME];
}pagina;

int cria_registro(int arquivo_id, registro reg); //Responsável por inserir um novo registro em uma página
