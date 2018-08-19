#ifndef LINK_H_
#define LINK_H_

#include "pagina.h"

typedef struct lista_visitados Visitados;

/*
  Tipoitem Link (tipo opaco)
  Estrutura do tipo a ser definida na implementação do TAD. Deve conter o campo:
  -nome (string)
  -nome_arq (string)
*/
typedef struct link Link;

/*
  Tipo que define a lista de itens do tipo Link (tipo opaco)
  Estrutura interna definida na implementação do TAD.
*/
typedef struct listalinks ListaLinks;

/* Inicializa uma lista vazia
*  inputs: nenhum
*  outputs: sentinela inicializado
*  pré-condição: nenhuma
*  pós-condição: lista inicializada e vazia
*/
ListaLinks* geralista_links();

/* checa se existe link para a pagina "nome" na lista dada
*  inputs: "nome" dado ao link (página a qual o link se refere) e a lista de links
*  outputs: retorna 0 se existir o link e 1 caso contrário
*  pré-condição: lista não nula
*  pós-condição: lista de links não alterada
*/
int caminho2(char* nome, ListaLinks* links);

/* Varre um vetor que contém os links visitados para retornar um inteiro booleano em relação a ocorrência do link na lista
*  inputs: nome do link a ser verificado, o vetor com os links visitados e um int que representa a primeira posição vazia do vetor
*  outputs: retorna 0 caso o link ja tenha sido visitado e 1 caso contrário
*  pré-condição: vetor está definido
*  pós-condição: vetor não alterado
*/
int foivisitado(char* nome, char** visitados, int* c);

/* Função recursiva que varre listas de links para verificar a existência de um caminho
*  inputs: nome do link procurado, a lista de links, uma lista de páginas, um vetor com os links visitados e o endereço de c
*  outputs: retorna 0 se houver caminho e 1 caso não haja
*  pré-condição: lista de links e de paginas não nula
*  pós-condição: nenhuma lista alterada
*/
int novocaminho2(char* nome, ListaLinks* links, void* paginas, char** visitados, int* c);

/* Função auxiliar responsável por criar o vetor visitados, chamar a função novocaminho2 e liberar o espaço alocado em visitados
*  inputs: nome do link procurado, a lista de links e a de páginas
*  outputs: retorna o que a função novocaminho2 retornar
*  pré-condição: lista de links não nula
*  pós-condição: mémoria alocada é liberada e lista de links não alterada
*/
int novocaminho(char* nome, ListaLinks* links, void* paginas);

/* Insere um novo Link na lista
*  inputs: nome ao qual o link faz referencia, nome do arquivo que representa o link e a lista
*  outputs: retorna 0 se ocorrer normalmente e 1 caso o link já exista na lista
*  pré-condição: lista não nula
*  pós-condição: link inserido ao final da lista
*/
int insere_link(char* nome, char* nome_arq, ListaLinks* links);

/* retira e libera um link de uma lista de links
*  inputs: o "nome" do link e uma lista de links
*  outputs: retorna 0 caso ocorra e 1 caso o link nao exista
*  pré-condição: lista não nula e link existente
*  pós-condição: link retirado e memória liberada
*/
int retira_link(char* nome, ListaLinks* links);

/* Imprime uma lista de links
*  inputs: um arquivo para realizar a impessão e a lista de links
*  outputs: nenhum
*  pré-condição: lista de links não nula e arquivo existente
*  pós-condição: lista de links impressa e não alterada
*/
void imprimelinks(FILE *arquivo, ListaLinks* links);
/* abre o arquivo e imprime todos os links com .txt na frente*/

/* Libera toda a memória alocada pela lista de links e pelos links
*  inputs: lista de links
*  outputs: nenhum
*  pré-condição: lista de links existe
*  pós-condição: toda a memória é liberada
*/
void free_links(ListaLinks* links);

#endif
