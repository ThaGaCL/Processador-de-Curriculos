#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "../prog2lattes/libdir.h"

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
    char names[100];
    int quantidade;
} pasta;

typedef struct dados{
    pasta *xpasta;
    int tamanhoPasta;
    estrato nome;
    int quantidade;
} tdados;

void setNames(char *line,tdados *xdados){


    for (int i = 0; i < 9; i++)
    {
        //get the last three characters of the line
        char *lastThree = line + strlen(line) - 3;
        

        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
        

            printf("%s\n", nome);
        }

    }

}

void getLines(FILE *arq, tdados *xdados){
    char line[LINESIZE+1];
    
    fgets(line, LINESIZE, arq);
    while(!feof(arq)){
        setNames(line, xdados);
        fgets(line, LINESIZE, arq);
    }


}

void inicializaEstratos(tdados *xdados){
   
    char* path = "qualis-periodicos.txt";
    
    for (int i = 0; i < 9; i++)
    {
        xdados[i].nome = i;
        xdados[i].quantidade = 0;
        xdados[i].tamanhoPasta = 0;
        xdados[i].xpasta = NULL;
    }


    FILE *arq = openFile(path);
    getLines(arq, xdados);
    fclose(arq);

}


int main()
{

    tdados *xdados = malloc(sizeof(tdados) * 9);
    inicializaEstratos(xdados);

    printf("\n");

    free(xdados);

    return 0;
}
