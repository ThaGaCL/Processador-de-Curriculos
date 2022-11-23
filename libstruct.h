#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define QTD_E 10
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

typedef struct pesquisador{
    char *nome;
    int estratos[QTD_E];
} tpesquisador;

typedef struct pesquisadores{
    tpesquisador *pesquisador;
    int qtdPesquisadores;
} tpesquisadores;

typedef struct pasta{
    char *titulo;
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

void setPerToRes(tdados *xdados, tpesquisador *xpesquisador);

void inicializaStructRes(tpesquisadores *xpesquisadores);

void inicializaRes(tpesquisadores *xpesquisadores, char *nome);

void printPer(tdados *xdados);

void printConf(tdados *xdados);

void setPerNames(char *line,tdados *xdados);

void setConfNames(char *line,tdados *xdados);

void addPerToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores);

void freeDados(tdados *xdados);

void printPeriodicosResumo(tdados *xdados);

void printNaoClassificados(tdados *xdados);