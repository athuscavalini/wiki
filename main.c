#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pagina.h"
#include "contribuicao.h"
#include "editor.h"
#include "link.h"

#define TAM 50

int main(int argc, char* argv[]){
  printf("\n%s\n",argv[1]);
  FILE* logerros;
  logerros = fopen("log.txt","w");
  FILE *arq_comandos;
  char comando[TAM];
  char entrada1[TAM];
  char entrada2[TAM];
  char entrada3[TAM];
  int key;
  ListaPaginas* paginas = geralista_paginas();
  ListaEditores* editores = geralista_editores();
  arq_comandos = fopen(argv[1],"r");
  printf("\nArquivo de comandos carregado...\n");
  fscanf(arq_comandos,"%s",comando);
  while(!feof(arq_comandos)){
    key = 9;
    if (strcmp(comando,"INSEREPAGINA") == 0){
      printf("inserindo pagina\n");
      fscanf(arq_comandos,"%s %s",entrada1,entrada2);
      inserepagina(entrada1,entrada2,paginas);
    }
    if (strcmp(comando,"RETIRAPAGINA") == 0){
      printf("retirando pagina\n");
      fscanf(arq_comandos,"%s",entrada1);
      key = retirapagina(entrada1,paginas);
      if(key == 1){
        fprintf(logerros, "ERRO: a pagina %s nao existe\n", entrada1);
      }
    }
    if (strcmp(comando,"INSEREEDITOR") == 0){
      printf("inserindo editor\n");
      fscanf(arq_comandos,"%s",entrada1);
      key = insereeditor(entrada1,editores);
      if(key == 1) fprintf(logerros, "ERRO: o editor ja existe\n");
    }
    if (strcmp(comando,"RETIRAEDITOR") == 0){
      printf("retirando editor\n");
      fscanf(arq_comandos,"%s",entrada1);
      key = retiraeditor(entrada1,paginas,editores);
      if(key == 1) fprintf(logerros, "ERRO: o editor %s nao existe\n", entrada1);
    }
    if (strcmp(comando,"INSERECONTRIBUICAO") == 0){
      printf("inserindo contribuicao\n");
      fscanf(arq_comandos,"%s %s %s",entrada1,entrada2,entrada3);
      key = inserecontribuicao(entrada1,entrada2,entrada3,paginas,editores);
      if(key == 1) fprintf(logerros, "ERRO: o editor %s nao existe\n", entrada2);
      if(key == 2) fprintf(logerros, "ERRO: a pagina %s nao existe\n", entrada1);
    }
    if (strcmp(comando,"RETIRACONTRIBUICAO") == 0){
      printf("retirando contribuicao\n");
      fscanf(arq_comandos,"%s %s %s",entrada1,entrada2,entrada3);
      key = retiracontribuicao(entrada1,entrada2,entrada3,paginas);
      if(key == 1) fprintf(logerros, "ERRO: o editor %s não tem autorizacao\n", entrada2);
      if(key == 2) fprintf(logerros, "ERRO: a contribuição %s nao existe\n", entrada3);
      if(key == 3) fprintf(logerros, "ERRO: a pagina %s nao existe\n", entrada1);
    }
    if (strcmp(comando,"INSERELINK") == 0){
      printf("inserindo link\n");
      fscanf(arq_comandos,"%s %s",entrada1,entrada2);
      key = inserelink(entrada1,entrada2,paginas);
      if(key == 1) fprintf(logerros, "ERRO: ja existe link de %s para %s\n",entrada1,entrada2);
      if(key == 2) fprintf(logerros, "ERRO: a pagina %s de origem nao existe\n", entrada1);
      if(key == 3) fprintf(logerros, "ERRO: a pagina %s de destino nao existe\n", entrada2);
    }
    if (strcmp(comando,"RETIRALINK") == 0){
      printf("retirando link\n");
      fscanf(arq_comandos,"%s %s",entrada1,entrada2);
      key = retiralink(entrada1,entrada2,paginas);
      if(key == 2) fprintf(logerros, "ERRO: nao existe link de %s para %s\n", entrada1, entrada2);
      if(key == 1) fprintf(logerros, "EROO: a pagina %s de origem nao existe\n", entrada1);
    }
    if (strcmp(comando,"CAMINHO") == 0){
      printf("checando caminho\n");
      fscanf(arq_comandos,"%s %s",entrada1,entrada2);
      key = caminho(entrada1,entrada2,paginas);
      if(key == 0) fprintf(logerros, "HA CAMINHO DA PAGINA %s PARA %s\n", entrada1, entrada2);
      if(key == 1) fprintf(logerros, "NAO HA CAMINHO DA PAGINA %s PARA %s\n", entrada1, entrada2);
    }
    if (strcmp(comando,"IMPRIMEPAGINA") == 0){
      printf("imprimindo pagina\n");
      fscanf(arq_comandos,"%s",entrada1);
      key = imprimepagina(entrada1,paginas);
      if(key == 1) fprintf(logerros, "ERRO: a pagina %s nao existe\n", entrada2);
    }
    if (strcmp(comando,"IMPRIMEWIKED") == 0){
      printf("imprimindo wiked\n");
      key = imprimewiked(paginas);
      if(key == 1) fprintf(logerros,"ERRO: nao existem paginas. WikED! vazia!\n");
    }
    if (strcmp(comando,"FIM") == 0){
      printf("finalizando...\n");
      fim(paginas,editores);
      printf("FINALIZADO!\n");
    }
    fscanf(arq_comandos,"%s",comando);
  }
  fclose(arq_comandos);
  fclose(logerros);
  return 0;
}
