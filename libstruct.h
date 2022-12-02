// libstruct.h
// Thales Carvalho
// BCC 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "edit-distance.h"


#define QTD_E 10
#define LINESIZE 1024
typedef enum{
    A1,
    A2,
    A3,
    A4,
    B1,
    B2,
    B3,
    B4,
    C,
    NC
} estrato;

typedef struct pesquisadores{
    int qtdPesquisadores;
    char *pesquisador[LINESIZE+1];
    int **estratosPer;
    int **estratosConf;
} tpesquisadores;

typedef struct pasta{
    char *titulo;
    int ano;
    int quantidade;
} pasta;

typedef struct dados{
    estrato nome;
    pasta *periodico;
    pasta *conferencia;
    int qtdPeriodicos;
    int qtdConferencias;
    int quantidade;
} tdados;

// ----------* ---------- FUNCOES DA STRUCT DE DADOS ----------*----------

// Imprime os periodicos presentes na Struct de Dados
void printPer(tdados *xdados);

// Imprime as conferencias presentes na Struct de Dados
void printConf(tdados *xdados);

// Insere o nome do Periodico na Struct de Dados
void setPerNames(char *line,tdados *xdados);

// Insere o nome da Conferencia na Struct de Dados
void setConfNames(char *line,tdados *xdados);

// Insere o nome do periocico na Struct de Dados
int addPerToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores);

// Insere os periodicos do curriculo na Struct de Dados
int addConfToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores);

// Libera a memoria alocada para a struct de dados
void freeDados(tdados *xdados);

// ----------*----------*----------*----------*----------*----------*----------

// ----------* ---------- FUNCOES DA STRUCT DE PESQUISADORES ----------*----------

// Inicializa a struct de pesquisadores
int inicializaStructRes(tpesquisadores *xpesquisadores, int dirSize);

// Inicializa um Pesquisador
int inicializaRes(tpesquisadores *xpesquisadores, char *nome);

// Libera a memoria alocada para a struct de pesquisadores
void freeStructRes(tpesquisadores *xpesquisadores, int dirSize);

// ----------*----------*----------*----------*----------*----------*----------

// ----------* ---------- FUNCOES DE IMPRESSAO ----------*----------

// Imprime o Resumo dos Periodicos
void printPeriodicosResumo(tdados *xdados);

// Imprime o Resumo das Conferencias
void printConfereciasResumo(tdados *xdados);

// Imprime o Resumo das Conferencias
void printNaoClassificados(tdados *xdados);

// Imprime o resumo dos Pesquisadores   
void printResumoRes(tpesquisadores *xpesquisadores);

// ----------*----------*----------*----------*----------*----------