#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contribuicao.h"

struct contribuicao{
  char* nome;
  char* editor;
  int publicado; // 1 representa que a contribuição está publicada, 0 que não.
  Contribuicao* prox;
};

struct listacontribuicoes{
  Contribuicao* prim;
  Contribuicao* ult;
};

ListaContribuicoes* geralista_contribuicoes(){
  ListaContribuicoes* contribuicoes = (ListaContribuicoes*)malloc(sizeof(ListaContribuicoes));
  contribuicoes->prim = NULL;
  contribuicoes->ult = NULL;
  return contribuicoes;
}

int insere_contribuicao(ListaContribuicoes* contribuicoes, char* nome, char* editor, ListaEditores* editores){
  if(existeeditor(editor,editores) == 1){
    return 1; //o editor nao existe;
  }
  if(contribuicoes->prim == NULL){
    contribuicoes->prim = (Contribuicao*)malloc(sizeof(Contribuicao));
    contribuicoes->ult = contribuicoes->prim;
  }
  else{
    contribuicoes->ult->prox = (Contribuicao*)malloc(sizeof(Contribuicao));
    contribuicoes->ult = contribuicoes->ult->prox;
  }
  contribuicoes->ult->nome = (char*)malloc(strlen(nome)+1);
  strcpy(contribuicoes->ult->nome, nome);
  contribuicoes->ult->editor = (char*)malloc(strlen(editor)+1);
  strcpy(contribuicoes->ult->editor, editor);
  contribuicoes->ult->publicado = 1;
  contribuicoes->ult->prox = NULL;
  return 0;
}

int retira_contribuicao(ListaContribuicoes* contribuicoes, char* nome, char* editor){
  if(contribuicoes->prim == NULL){
    return 2; //Lista vazia
  }
  Contribuicao* count = contribuicoes->prim;
  while(count != NULL){
    if(strcmp(count->nome, nome) == 0){
      if(strcmp(count->editor, editor) == 0){
        count->publicado = 0;
        return 0;
      }
      return 1; //Editor não autorizado
    }
    count = count->prox;
  }
  return 2; //Não existe contribuição com o nome dado.
}

void exclui_contribuicoes(ListaContribuicoes* contribuicoes, char* editor){
  if(contribuicoes->prim == NULL){
    return;
  }
  Contribuicao* c = contribuicoes->prim;
  Contribuicao* ant = NULL;
  while(c != NULL){
    if(strcmp(c->editor, editor) == 0){
      if(c == contribuicoes->prim && c == contribuicoes->ult){ //Verifica se só há uma contribuição na lista
        contribuicoes->prim = contribuicoes->ult = NULL;
        free(c->nome);
        free(c->editor);
        free(c);
        return;
      }else{
        if(c == contribuicoes->ult){ //Verifica se a contribuição analisada é a ultima.
          contribuicoes->ult = ant;
          ant->prox = NULL;
          free(c->nome);
          free(c->editor);
          free(c);
          return;
        }
        if(c == contribuicoes->prim){ //Verifica se a contribuição analisada é a primeira.
          contribuicoes->prim = c->prox;
          free(c->nome);
          free(c->editor);
          free(c);
        }else{
          ant->prox = c->prox; //Caso seja uma contribuição do "meio" da lista.
          free(c->nome);
          free(c->editor);
          free(c);
        }
      }
    }
    ant = c;
    c = c->prox;
  }
}

void imprimehistorico_contribuicoes(ListaContribuicoes* contribuicoes, FILE *arquivo){
  Contribuicao* aux = contribuicoes->prim;
  fprintf(arquivo,"--> Historico de contribuicoes\n");
  while (aux != NULL){
    fprintf(arquivo,"%s %s",aux->editor,aux->nome);
    if (aux->publicado == 0) fprintf(arquivo,"  <<retirada>>");
    fprintf(arquivo,"\n");
    aux = aux->prox;
  }
}

void imprimecontribuicoes(ListaContribuicoes* contribuicoes, FILE *arquivo){
  Contribuicao* aux = contribuicoes->prim;
  FILE *c;
  fprintf(arquivo,"--> Textos\n");
  while(aux != NULL){
    if (aux->publicado == 1){
      c = fopen(aux->nome,"r");
      fprintf(arquivo,"\n\n-------- %s (%s) --------\n\n",aux->nome,aux->editor);
      int a;
      while ((a = fgetc(c)) != EOF){
        fputc(a,arquivo);
      }
      fclose(c);
    }
    aux = aux->prox;
  }
}

void free_contribuicoes(ListaContribuicoes* contribuicoes){
  if(contribuicoes->prim == NULL){
    free(contribuicoes);
    return;
  }
  Contribuicao* ant = NULL;
  Contribuicao* c = contribuicoes->prim;
  while(c != NULL){
    ant = c;
    c = c->prox;
    free(ant->nome);
    free(ant->editor);
    free(ant);
  }
  free(contribuicoes);
}
