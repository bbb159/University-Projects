

typedef struct{
    int espaco_livre;
    int id_bloco;
}diretorio_blocos;

typedef struct{
    int arquivo_id;
    diretorio_blocos* header;
}linha_tabela;

typedef struct{
    linha_tabela tabelas[5];
}diretorio_arquivos;

//FUNÇÕES

//int inicializa_ga(int num_tabelas); //Inicializa diretorio de arquivos e ja define um numero maximo de tabelas que pode haver

int criar_tabela(char* tabela); //Criar uma nova tabela e chama 'cria_diretorio' para alocar um espaço no diretorio_arquivos para essa nova tabela(arquivo)

int cria_diretorio(int arquivo_id, int id_bloco); // Responsável por alocar um espaço no diretorio de arquivos (recebe um arquivo id e um id_bloco proveniente do GED(funcao aloca bloco) para ser a header page) e retornar o endereço da tabela nova

int checar_espaco_blocos(int arquivo_id, int espaco_necessario); //Reponsável por checar se existe bloco com espaço livre (do tamanho do espaco necessario ou menor), e se sim, verificar se o bloco ja esta carregado na memoria, se nao, carregar.

int cria_pagina(void); //Responsável por chamar GED para alocar um novo bloco e por criar uma nova página e retornar endereço dessa nova pagina

int atualiza_espaco(int arquivo_id, int id_pagina, int num); //Reponsável por atualizar o campo espaço livre de uma pagina(o campo 'num' teria valor 1 ou -1)

int busca_pagina(int id_arquivo, int id_pagina); //Responsável por retornar o endereço de uma página


//arquivo_id = id da linha_tabela
