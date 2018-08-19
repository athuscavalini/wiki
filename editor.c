#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

struct editor{
  char* nome;
  Editor* prox;
};

struct listaeditores{
  Editor* prim;
  Editor* ult;
};

ListaEditores* geralista_editores(){
  ListaEditores* editores = (ListaEditores*)malloc(sizeof(ListaEditores));
  editores->prim = NULL;
  editores->ult = NULL;
  return editores;
}

int existeeditor(char* nome, ListaEditores* editores){
  Editor* aux = editores->prim;
  while (aux!=NULL){
    if (strcmp(aux->nome,nome) == 0) return 0;
    aux = aux->prox;
  }
  return 1;
}

int insereeditor(char* nome, ListaEditores* editores){
  if (existeeditor(nome,editores) == 0) return 1; // O editor já existe.
  if (editores->prim == NULL){
    editores->prim = (Editor*)malloc(sizeof(Editor));
    editores->ult = editores->prim;
  }else{
    editores->ult->prox = (Editor*)malloc(sizeof(Editor));
    editores->ult = editores->ult->prox;
  }
  editores->ult->nome = (char*)malloc(strlen(nome)+1);
  strcpy(editores->ult->nome,nome);
  editores->ult->prox = NULL;
  return 0;
}

int retira_editor(char* nome, ListaEditores* editores){
  if (editores->prim == NULL) return 1; //lista de editores vazia
  Editor* ant = editores->prim;
  Editor* aux = editores->prim->prox;
  if (strcmp(ant->nome,nome) == 0){
    editores->prim = editores->prim->prox;
    if (editores->ult == ant) editores->ult = NULL;
    free(ant->nome);
    free(ant);
    return 0;
  }
  while (aux != NULL){
    if (strcmp(nome,aux->nome) == 0){
      ant->prox = aux->prox;
      if (editores->ult == aux) editores->ult = NULL;
      free(aux->nome);
      free(aux);
      return 0;
    }
    ant = aux;
    aux = aux->prox;
  }
  return 1; //nao existe o editor;
}

void free_editores(ListaEditores* editores){
  Editor* ant = NULL;
  Editor* aux = editores->prim;
  while(aux != NULL){
    ant = aux;
    aux = aux->prox;
    free(ant->nome);
    free(ant);
  }
  free(editores);
}
