#define MEMSZ 5 //P�ginas(frames) que podem ser comportadas na mem�ria

pagina* memoria; //Array de p�ginas para simular mem�ria


typedef struct{
    int pin_count;
    int dirty_bit;
    int id_bloco;
    //struct pagina* addr_pagina;
} frame_info;




typedef struct {
    frame_info frames[MEMSZ];
} gbp;





//FUN��ES

//int inicializa_gbp(int TAM_MEMORIA); //Inicializa GBP.

pagina* verifica_quant_frames(int arquivo_id); //Checa se existem frames livres e retorna uma p�gina(se tiver que criar, chama o 'cria_pagina')

int inserir_registro(char *str); //Responsavel por inserir um registro STR. Comunica com GA e chama o checa_espaco_bloco

int gbp_lru(void); //Respons�vel por aplicara pol�tica de substitui��o Least Recently Used


//bloco -> memoria
int habilitar_transferencia(void);// Chama a funcao LER BLOCO do GED pra transferir blcoo para a memoria

int busca_registro(int arquivo_id, char *str); //Respons�vel por retornar o numero do slot de um registro

int atualiza_registro(int arquivo_id, int id_pagina, registro reg, int slot); //Respons�vel por atualizar um registro

int remover_registro(int arquivo_id, int id_pagina, int chave); //Respons�vel por remover um registro e atualizar espa�o livre

int escrever_pagina(pagina pagina); //Respons�vel por escrever uma p�gina no disco

int numero_frame(int id_bloco); //Respons�vel por retornar numero do frame de um determinado bloco

void frame_modificado(pagina pagina); //Respons�vel por alterar o campo dirty_bit e dizer que p�gina foi alterada

void pagina_setUse(pagina pagina, int flag); //Se a pagina estiver em uso: flag = 1 -> incrementar pin_count; se flag = 0 -> decrementa pin_count

