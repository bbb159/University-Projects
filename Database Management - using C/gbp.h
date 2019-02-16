#define MEMSZ 5 //Páginas(frames) que podem ser comportadas na memória

pagina* memoria; //Array de páginas para simular memória


typedef struct{
    int pin_count;
    int dirty_bit;
    int id_bloco;
    //struct pagina* addr_pagina;
} frame_info;




typedef struct {
    frame_info frames[MEMSZ];
} gbp;





//FUNÇÕES

//int inicializa_gbp(int TAM_MEMORIA); //Inicializa GBP.

pagina* verifica_quant_frames(int arquivo_id); //Checa se existem frames livres e retorna uma página(se tiver que criar, chama o 'cria_pagina')

int inserir_registro(char *str); //Responsavel por inserir um registro STR. Comunica com GA e chama o checa_espaco_bloco

int gbp_lru(void); //Responsável por aplicara política de substituição Least Recently Used


//bloco -> memoria
int habilitar_transferencia(void);// Chama a funcao LER BLOCO do GED pra transferir blcoo para a memoria

int busca_registro(int arquivo_id, char *str); //Responsável por retornar o numero do slot de um registro

int atualiza_registro(int arquivo_id, int id_pagina, registro reg, int slot); //Responsável por atualizar um registro

int remover_registro(int arquivo_id, int id_pagina, int chave); //Responsável por remover um registro e atualizar espaço livre

int escrever_pagina(pagina pagina); //Responsável por escrever uma página no disco

int numero_frame(int id_bloco); //Responsável por retornar numero do frame de um determinado bloco

void frame_modificado(pagina pagina); //Responsável por alterar o campo dirty_bit e dizer que página foi alterada

void pagina_setUse(pagina pagina, int flag); //Se a pagina estiver em uso: flag = 1 -> incrementar pin_count; se flag = 0 -> decrementa pin_count

