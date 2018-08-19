#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

struct link{
  char* nome;
  char* nome_arq;
  Link* prox;
};

struct listalinks{
  Link* prim;
  Link* ult;
};

int foivisitado(char* nome, char** visitados, int* c){
  for(int i=0;i<*c;i++){
    if (strcmp(visitados[i],nome)==0) return 0;
  }
  return 1;
}

int novocaminho2(char* nome, ListaLinks* links, void* paginas, char** visitados, int* c){
  Link* link = links->prim;
  int k = 1;
  while(link != NULL){
    if(strcmp(link->nome,nome)==0){
      return 0;
    }
    if(foivisitado(link->nome,visitados,c)==1){
      visitados[*c] = (char*)malloc(strlen(link->nome)+1);
      strcpy(visitados[*c],link->nome);
      (*c)++;
      k = novocaminho2(nome,(ListaLinks*)(endereco_listalinks(link->nome,(ListaPaginas*)paginas)), paginas, visitados, c);
      if (k == 0) return 0;
    }
    link = link->prox;
  }
  return 1;
}

ListaLinks* geralista_links(){
  ListaLinks* links = (ListaLinks*)malloc(sizeof(ListaLinks));
  links->prim = NULL;
  links->ult = NULL;
  return links;
}

int novocaminho(char* nome, ListaLinks* links, void* paginas){
  char* visitados[1000];
  int c = 0;
  int i = novocaminho2(nome,links,paginas,visitados,&c);
  for(int j = 0; j < c; j++){
    free(visitados[j]);
  }
  return i;
}

int caminho2(char* nome, ListaLinks* links){
  Link* aux = links->prim;
  while (aux!=NULL){
    if (strcmp(aux->nome,nome)==0) return 0;
    aux = aux->prox;
  }
  return 1;
}

int insere_link(char* nome, char* nome_arq, ListaLinks* links){
  if (caminho2(nome,links) == 0) return 1; //link já existe
  if (links->prim == NULL){
    links->prim = (Link*)malloc(sizeof(Link));
    links->ult = links->prim;
  }else{
    links->ult->prox = (Link*)malloc(sizeof(Link));
    links->ult = links->ult->prox;
  }
  links->ult->nome = (char*)malloc(strlen(nome)+1);
  strcpy(links->ult->nome, nome);
  links->ult->nome_arq = (char*)malloc(strlen(nome_arq)+1);
  strcpy(links->ult->nome_arq, nome_arq);
  links->ult->prox = NULL;
  return 0;
}

int retira_link(char* nome, ListaLinks* links){
  if (links->prim == NULL) return 2; //nao existem links. lista vazia.
  Link* ant = links->prim;
  Link* aux = links->prim->prox;
  if (strcmp(ant->nome,nome) == 0){
    links->prim = links->prim->prox;
    if (links->ult == ant) links->ult = NULL;
    free(ant->nome);
    free(ant->nome_arq);
    free(ant);
    return 0;
  }
  while (aux != NULL){
    if (strcmp(nome,aux->nome) == 0){
      ant->prox = aux->prox;
      if (links->ult == aux) links->ult = NULL;
      free(aux->nome);
      free(aux->nome_arq);
      free(aux);
      return 0;
    }
    ant = aux;
    aux = aux->prox;
  }
  return 2; //link nao encontrado
}

void imprimelinks(FILE *arquivo, ListaLinks* links){
  Link* aux = links->prim;
  fprintf(arquivo,"--> Links\n");
  while (aux!= NULL){
    fprintf(arquivo,"%s %s\n", aux->nome, aux->nome_arq);
    aux = aux->prox;
  }
}

void free_links(ListaLinks* links){
  Link* ant = NULL;
  Link* aux = links->prim;
  while(aux != NULL){
    ant = aux;
    aux = aux->prox;
    free(ant->nome);
    free(ant->nome_arq);
    free(ant);
  }
  free(links);
}
