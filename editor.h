#ifndef EDITOR_H_
#define EDITOR_H_

/*
  Tipoitem Editor (tipo opaco)
  Estrutura do tipo definida na implementação do TAD. Deve conter o campo:
  -nome (string)
*/
typedef struct editor Editor;

/*
  Tipo que define a lista de itens do tipo Editor (tipo opaco)
  Estrutura interna definida na implementação do TAD
*/
typedef struct listaeditores ListaEditores;

/* Inicializa uma lista vazia
*  inputs: nenhum
*  outputs: sentinela inicializado
*  pré-condição: nenhuma
*  pós-condição: lista inicializada e vazia
*/
ListaEditores* geralista_editores();

/* Informa sobre a existência ou não de um editor na lista
*  inputs: nome do editor e a lista de editores
*  outputs: retorna 0 se o editor existir na lista e 1 caso o contrário
*  pré-condição: lista não nula
*  pós-condição: Informação sobre a existência ou não de um editor na lista através de um inteiro
*/
int existeeditor(char* nome, ListaEditores* editores);

/* Insere um novo editor na lista
*  inputs: nome do editor e a lista de editores
*  outputs: retorna 0 se ocorreu como o esperado e 1 caso o editor já exista
*  pré-condição: lista não nula
*  pós-condição: editor inserido ao final da lista
*/
int insereeditor(char* nome, ListaEditores* editores);

/* Inicializa uma lista vazia
*  inputs: nome do editor e a lista de editores
*  outputs: retorna 0 se ocorreu como o esperado e 1 caso o editor não exista
*  pré-condição: lista não nula e editor existente
*  pós-condição: editor retirado da respectiva lista
*/
int retira_editor(char* nome, ListaEditores* editores);

/* Libera a memória alocada na lista de editores
*  inputs: lista de editores
*  outputs: nenhum
*  pré-condição: lista não nula
*  pós-condição: toda a memória usada para armazenar a lista de editores liberada
*/
void free_editores(ListaEditores* editores);

#endif
