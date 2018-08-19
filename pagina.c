#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagina.h"

struct pagina{
  char* nome;
  char* nome_arq;
  ListaContribuicoes* contribuicoes;
  ListaLinks* links;
  Pagina* prox;
};

struct listapaginas{
  Pagina* prim;
  Pagina* ult;
};

ListaPaginas* geralista_paginas(){
  ListaPaginas* paginas = (ListaPaginas*)malloc(sizeof(ListaPaginas));
  paginas->prim = NULL;
  paginas->ult = NULL;
  return paginas;
}

void* endereco_listalinks(char* pagina, ListaPaginas* paginas){
  if (paginas->prim == NULL) return NULL;
  Pagina* aux = paginas->prim;
  while (aux != NULL){
    if (strcmp(aux->nome,pagina) == 0) return aux->links;
    aux = aux->prox;
  }
  return NULL;
}

Pagina* enderecopagina(char* pagina, ListaPaginas* paginas){
  if (paginas->prim == NULL) return NULL;
  Pagina* aux = paginas->prim;
  while (aux != NULL){
    if (strcmp(aux->nome,pagina) == 0) return aux;
    aux = aux->prox;
  }
  return NULL;
}

void inserepagina(char* nome, char* nome_arq, ListaPaginas* paginas){
  if (paginas == NULL) return;
  if (paginas->prim == NULL){
    paginas->prim = (Pagina*)malloc(sizeof(Pagina));
    paginas->ult = paginas->prim;
  }else{
    paginas->ult->prox = (Pagina*)malloc(sizeof(Pagina));
    paginas->ult = paginas->ult->prox;
  }
  paginas->ult->nome = (char*)malloc(strlen(nome)+1);
  strcpy(paginas->ult->nome,nome);
  paginas->ult->nome_arq = (char*)malloc(strlen(nome_arq)+1);
  strcpy(paginas->ult->nome_arq,nome_arq);
  paginas->ult->contribuicoes = geralista_contribuicoes();
  paginas->ult->links = geralista_links();
  paginas->ult->prox = NULL;
}

int retirapagina(char* nome, ListaPaginas* paginas){
  if (paginas->prim == NULL){
    return 1; // A página não existe.
  }
  Pagina* ant = paginas->prim;
  Pagina* aux = paginas->prim->prox;
  if (strcmp(ant->nome,nome) == 0){
    paginas->prim = paginas->prim->prox;
    if (paginas->ult == ant) paginas->ult = NULL;
    free(ant->nome);
    free(ant->nome_arq);
    free_contribuicoes(ant->contribuicoes);
    free_links(ant->links);
    free(ant);
    return 0;
  }
  while (aux != NULL){
    if (strcmp(nome,aux->nome) == 0){
      ant->prox = aux->prox;
      if (paginas->ult == aux) paginas->ult = NULL;
      free(aux->nome);
      free(aux->nome_arq);
      free_contribuicoes(aux->contribuicoes);
      free_links(aux->links);
      free(aux);
      return 0;
    }
    ant = aux;
    aux = aux->prox;
  }
  return 1;
}

int inserecontribuicao(char* pagina, char* editor, char* contribuicao, ListaPaginas* paginas, ListaEditores* editores){
  Pagina* end_pagina = enderecopagina(pagina,paginas);
  if (end_pagina == NULL){
    return 2; // A pagina não existe.
  }
  return insere_contribuicao(end_pagina->contribuicoes, contribuicao, editor, editores);
}

int retiracontribuicao(char* pagina, char* editor, char* contribuicao, ListaPaginas* paginas){
Pagina* end_pagina = enderecopagina(pagina,paginas);
if (end_pagina == NULL){
  return 3; // A página não existe.
}
return retira_contribuicao(end_pagina->contribuicoes, contribuicao, editor);
}

int retiraeditor(char* nome, ListaPaginas* paginas, ListaEditores* editores){
  Pagina* p = paginas->prim;
  while (p != NULL) {
    exclui_contribuicoes(p->contribuicoes,nome);
    p = p->prox;
  }
  return retira_editor(nome,editores);
}

int inserelink(char* pagina_origem, char* pagina_destino, ListaPaginas* paginas){
  Pagina* end_pagina_origem = enderecopagina(pagina_origem, paginas);
  Pagina* end_pagina_destino = enderecopagina(pagina_destino, paginas);
  if (end_pagina_origem == NULL){
    return 2; //A pagina origem não existe.
  }
  if (end_pagina_destino == NULL){
    return 3; //A página destino não existe.
  }
  return insere_link(pagina_destino, end_pagina_destino->nome_arq, end_pagina_origem->links);
}

int retiralink(char* pagina_origem, char* pagina_destino, ListaPaginas* paginas){
  Pagina* end_pagina = enderecopagina(pagina_origem,paginas);
  if (end_pagina == NULL) return 1; //A página não existe
  return retira_link(pagina_destino,end_pagina->links);
}

int caminho(char* pagina_origem, char* pagina_destino, ListaPaginas* paginas){
  // Visitados* visitados = NULL;
  Pagina* end_pagina = enderecopagina(pagina_origem,paginas);
  Pagina* end_pagina_destino = enderecopagina(pagina_destino, paginas);
  if (end_pagina == NULL){
    return 2; //A página origem não existe
  }
  if (end_pagina_destino == NULL){
    return 3; //A página destino não existe.
  }
  return novocaminho(pagina_destino,end_pagina->links,paginas);
  //return caminho2(pagina_destino,end_pagina->links);
}

int imprimepagina(char* nome, ListaPaginas* paginas){
  Pagina* pagina = enderecopagina(nome,paginas);
  if (pagina == NULL) return 1; //a pagina nao existe;
  FILE *arquivo;
  arquivo = fopen (pagina->nome_arq,"w");
  fprintf(arquivo,"%s\n\n",pagina->nome);
  imprimehistorico_contribuicoes(pagina->contribuicoes,arquivo);
  fprintf(arquivo,"\n\n");
  imprimelinks(arquivo,pagina->links);
  fprintf(arquivo,"\n\n");
  imprimecontribuicoes(pagina->contribuicoes,arquivo);
  fclose(arquivo);
  return 0;
}

int imprimewiked(ListaPaginas* paginas){
  Pagina* pagina = paginas->prim;
  if (pagina == NULL) return 1;
  while (pagina != NULL){
    imprimepagina(pagina->nome,paginas);
    pagina = pagina->prox;
  }
  return 0;
}

void fim(ListaPaginas* paginas, ListaEditores* editores){
  Pagina* aux = paginas->prim;
  Pagina* ant = NULL;
  while (aux != NULL){
    ant = aux;
    aux = aux->prox;
    free(ant->nome);
    free(ant->nome_arq);
    free_contribuicoes(ant->contribuicoes);
    free_links(ant->links);
    free(ant);
  }
  free(paginas);
  free_editores(editores);
}
