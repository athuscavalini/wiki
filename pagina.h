#ifndef PAGINA_H_
#define PAGINA_H_

#include "link.h"
#include "contribuicao.h"
#include "editor.h"

/*
  Tipo Pagina (tipo opaco)
  Estrutura do tipo a ser definida na implementação do TAD.
*/
typedef struct pagina Pagina;

/*
  Tipo que define a lista de itens do tipo Pagina (tipo opaco)
  Estrutura interna definida na implementação do TAD.
*/
typedef struct listapaginas ListaPaginas;

/* Inicializa uma lista vazia
*  inputs: nenhum
*  outputs: lista inicializada
*  pré-condição: nenhuma
*  pós-condição: lista inicializada e vazia
*/
ListaPaginas* geralista_paginas();

/* Retorna um ponteiro para uma lista de links dentro de uma página
*  inputs: nome da página e a lista de páginas
*  outputs: um void pointer para a lista de links
*  pré-condição: lista de páginas não nula e página existe
*  pós-condição: lista de páginas não alterada
*/
void* endereco_listalinks(char* pagina, ListaPaginas* paginas);

/* Retorna um ponteiro pra uma página a partir de uma lista dada
*  inputs: nome da página e uma lista de páginas
*  outputs: ponteiro pra página
*  pré-condição: lista não nula e página existente
*  pós-condição: lista não alterada
*/
Pagina* enderecopagina(char* pagina, ListaPaginas* paginas);

/* Insere uma página em uma lista de páginas
*  inputs: nome da página, nome do arquivo correspondente e uma lista de páginas
*  outputs: retorna 0 caso a página seja inserida, e 1 caso a lista de páginas não exista
*  pré-condição: lista de páginas existe
*  pós-condição: nova página inserida e memória alocada
*/
void inserepagina(char* nome, char* nome_arq, ListaPaginas* paginas);

/* retira e libera uma página de uma lista dada (libera também a lista de links e de contribuições), além de retirar os links que fazem referência a esta página
*  inputs: nome da página e uma lista de páginas
*  outputs: retorna 0 se a função funcionar normalmente e 1 caso a página não exista
*  pré-condição: lista não nula
*  pós-condição: página retirada, memória liberada e links removidos
*/
int retirapagina(char* nome, ListaPaginas* paginas);

/* Insere uma contribuição em uma página
*  inputs: nome da página, nome do editor, nome da contribuicao, lista de páginas e uma lista de editores
*  outputs: retorna 0 se ocorrer normalmente, 1 caso o editor não exista e 2 caso a página não exista
*  pré-condição: listas não nulas, página e editor existem
*  pós-condição: contribuição inserida e lista de páginas e editores não alteradas
*/
int inserecontribuicao(char* pagina, char* editor, char* contribuicao, ListaPaginas* paginas, ListaEditores* editores);

/* retira uma contribuição de uma página
*  inputs: nome da página, nome do editor, nome do arquivo de contribuição e a lista de páginas
*  outputs: retorna 0 se ocorrer normalmente, 1 se o editor não for autorizado, 2 caso a contribuição não exista e 3 caso a página não exista
*  pré-condição: listas não nulas, pagina e contribuição existem e editor autorizado
*  pós-condição: contribuição retirada, lista de paginas não alterada
*/
int retiracontribuicao(char* pagina, char* editor, char* contribuicao, ListaPaginas* paginas);

/* Primeiramente retira e libera todas as contribuições da wikED pertencentes ao editor, e depois retira o editor da lista de editores
*  inputs: nome do editor, lista de páginas e de editores
*  outputs: retorna 0 se ocorrer normalmente e 1 caso o editor não exista
*  pré-condição: listas não nulas e editor existe
*  pós-condição: editor retirado e lista de páginas não alterada
*/
int retiraeditor(char* nome, ListaPaginas* paginas, ListaEditores* editores);

/* Insere um link em uma página
*  inputs: nome da página que recebe o link, nome da página a qual o link se refere e a lista de páginas
*  outputs: retorna 0 se o link for inserido, 1 caso o link já exista, 2 caso a página origem não exista e 3 caso a página destino não exista
*  pré-condição: lista não nula e páginas existem
*  pós-condição: link inserido e lista de páginas não alterada
*/
int inserelink(char* pagina_origem, char* pagina_destino, ListaPaginas* paginas);

/* Retira e libera um link de uma página
*  inputs: nome da página que recebe o link, nome da página a qual o link se refere e a lista de páginas
*  outputs: retorna 0 caso ocorra, 1 se a pagina de origem nao exista,
*  pré-condição: listas não nulas e páginas existem
*  pós-condição: link retirado e memória liberada
*/
int retiralink(char* pagina_origem, char* pagina_destino, ListaPaginas* paginas);

/* Verifica a existência de um caminho entre páginas através de links
*  inputs: nome da página origem, nome da página destino e a lista de páginas
*  outputs: retorna 0 caso haja caminho, 1 caso não haja, 2 caso a página origem não exista e 3 caso a página destino não exista
*  pré-condição: lista não nula e páginas existem
*  pós-condição: lista não alterada
*/
int caminho(char* pagina_origem, char* pagina_destino, ListaPaginas* paginas);

/* Cria um arquivo e imprime uma página da wikED (contribuições, links e historico)
*  inputs: nome da página e a lista de páginas
*  outputs: retorna 0 caso ocorra, e 1 caso a página dada não exista
*  pré-condição: lista não nula
*  pós-condição: página impressa e lista não alterada
*/
int imprimepagina(char* nome, ListaPaginas* paginas);

/* Imprime toda a wikED
*  inputs: lista de páginas
*  outputs: retorna 0 se ocorrer e 1 se a lista estiver vazia
*  pré-condição: lista não nula
*  pós-condição: wikED impressa e lista não alterada
*/
int imprimewiked(ListaPaginas* paginas);
/*roda a funcao imprimepagina em loop para todas as paginas, alem de criar o arquivo de editores (precisa???) */

/* Libera toda a memória alocada pela wikED
*  inputs: lista de páginas e de editores
*  outputs: nenhum
*  pré-condição: listas não nulas
*  pós-condição: toda memória alocada é liberada
*/
void fim(ListaPaginas* paginas, ListaEditores* editores);

#endif
