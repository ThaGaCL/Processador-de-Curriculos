#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "libdir.h"

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

const char *enumName(estrato c);

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

void getPerLines(FILE *arq, tdados *xdados);

void getConfLines(FILE *arq, tdados *xdados);

void inicializaEstratos(tdados *xdados, char *per, char *con);

