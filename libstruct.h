#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define QTD_E 9
typedef enum{
    A1,
    A2,
    A3,
    A4,
    B1,
    B2,
    B3,
    B4,
    C
} estrato;

typedef struct pesquisador{
    char *nome;
    int a1;
    int a2;
    int a3;
    int a4;
    int b1;
    int b2;
    int b3;
    int b4;
    int c;
} xpesquisador;

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

void printPer(tdados *xdados);

void printConf(tdados *xdados);

void setPerNames(char *line,tdados *xdados);

void setConfNames(char *line,tdados *xdados);

void addPerToStruct(tdados *xdados, char *nome);
