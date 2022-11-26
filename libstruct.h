#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

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

void setPerToRes(tdados *xdados, tpesquisadores *xpesquisadores);

// Inicializa a struct de pesquisadores
void inicializaStructRes(tpesquisadores *xpesquisadores, int dirSize);

// Inicializa um Pesquisador
void inicializaRes(tpesquisadores *xpesquisadores, char *nome);

// Imprime os periodicos presentes na Struct de Dados
void printPer(tdados *xdados);

// Imprime as conferencias presentes na Struct de Dados
void printConf(tdados *xdados);

// Insere o nome do Periodico na Struct de Dados
void setPerNames(char *line,tdados *xdados);

// Insere o nome da Conferencia na Struct de Dados
void setConfNames(char *line,tdados *xdados);

// Insere o nome do periocico na Struct de Dados
void addPerToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores);

// Libera a memoria alocada para a struct de dados
void freeDados(tdados *xdados);

// Imprime o Resumo dos Periodicos
void printPeriodicosResumo(tdados *xdados);

// Imprime o Resumo das Conferencias
void printNaoClassificados(tdados *xdados);

// Imprime o resumo dos Pesquisadores   
void imprimeResumoRes(tpesquisadores *xpesquisadores);
