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

const char *enumName(estrato c){
    switch (c)
    {
    case A1:
        return ("A1");
    case A2:
        return ("A2");
    case A3:
        return ("A3");
    case A4:
        return ("A4");
    case B1:
        return ("B1");
    case B2:
        return ("B2");
    case B3:
        return ("B3");
    case B4:
        return ("B4");
    case C:
        return ("C");
    default:
        return ("aaaaa");
    }
}


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

void inicializaEstratos(tdados *xdados);

