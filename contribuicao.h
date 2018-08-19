#ifndef CONTRIBUICAO_H_
#define CONTRIBUICAO_H_

#include "editor.h"
/*
  Tipo de item Contribuicao (tipo opaco)
  Estrutura do tipo a ser definida na implementação do TAD. Deve conter os campos:
  -nome (string)
  -editor (string)
*/
typedef struct contribuicao Contribuicao;

/*
  Tipo que define a lista de itens do tipo Contribuicao (tipo opaco)
  Estrutura interna deve ser definida na implementação do TAD
*/
typedef struct listacontribuicoes ListaContribuicoes;

/* Inicializa uma lista vazia
*  inputs: nenhum
*  outputs: sentinela inicializado
*  pré-condição: nenhuma
*  pós-condição: lista inicializada e vazia
*/
ListaContribuicoes* geralista_contribuicoes();

/* Insere uma nova contribuição no final da lista de contribuições
*  inputs: lista de contribuicoes, nome, nome do editor e a lista de editores
*  outputs: retorna 0 se a contribuição foi posicionada corretamente no final da lista, e 1 caso o editor não exista
*  pré-condição: lista não nula e editor existente
*  pós-condição: contribuição inserida ao final da lista
*/
int insere_contribuicao(ListaContribuicoes* contribuicoes, char* nome, char* editor, ListaEditores* editores);

/* Retira uma contribuição da lista
*  inputs: lista de contribuições, o nome da contribuição a ser retirada e o nome do editor responsável pela contribuição
*  outputs: retorna 0 se ocorreu normalmente, 1 se o editor não for compativel com o dono da contribuição e 2 se a contribuição não existir na lista
*  pré-condição: lista não nula e editor compatível
*  pós-condição: contribuição retirada da lista
*/
int retira_contribuicao(ListaContribuicoes* contribuicoes, char* nome, char* editor);

/* Libera a memória alocada das contribuições de um respectivo editor
*  inputs: lista de contribuições e o nome do editor
*  outputs: nenhum
*  pré-condição: lista não nula
*  pós-condição: todas as contribuições do editor retiradas e liberadas da lista
*/
void exclui_contribuicoes(ListaContribuicoes* contribuicoes, char* editor);

/* Imprime o histórico de contribuições em um arquivo texto
*  inputs: lista de contribuicoes e arquivo para saída
*  outputs: nenhum
*  pré-condição: lista não nula e arquivo aberto com possibilidade de escrita
*  pós-condição: impressao do historico de todas as contribuicoes no arquivo texto, indicando as que foram removidas pelo editor responsável
*/
void imprimehistorico_contribuicoes(ListaContribuicoes* contribuicoes, FILE *arquivo);

/* Imprime todas as contribuições de uma lista em um arquivo texto
*  inputs: lista de constribuicoes e arquivo para saída
*  outputs: nenhum
*  pré-condição: lista não nula e arquivo aberto com possibilidade de escrita
*  pós-condição: o arquivo contém as contribuicoes impressas em sequência
*/
void imprimecontribuicoes(ListaContribuicoes* contribuicoes, FILE *arquivo);

/* Apaga e libera a memória alocada de uma lista de contribuições
*  inputs: lista de contribuições
*  outputs: nenhum
*  pré-condição: lista não nula
*  pós-condição: toda a memória alocada para a lista é liberada
*/
void free_contribuicoes(ListaContribuicoes* contribuicoes);

#endif
