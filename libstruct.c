#include "libstruct.h"
#include "libutil.h"

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
    case NC:
        return ("NC");
    default:
        return ("");
    }
}

void printPer(tdados *xdados){
    for(int i = 0; i < QTD_E; i++){
        for(int j = 0; j <= xdados[i].qtdPeriodicos-1; j++){
             printf("%s\n", xdados[i].periodico[j].titulo);
        }
    }
}

void printConf(tdados *xdados){
    for(int i = 0; i < QTD_E; i++){
        for(int j = 0; j <= xdados[i].qtdConferencias-1; j++){
             printf("%s\n", xdados[i].conferencia[j].titulo);
        }
    }
}

void setPerNames(char *line,tdados *xdados){


    for (int i = 0; i < QTD_E-1; i++)
    {
        //get the last three characters of the line
        char *lastThree = line + strlen(line) - 3;
        

        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
            xdados[i].periodico[xdados[i].qtdPeriodicos].titulo = malloc(sizeof(char)*strlen(nome));    
            xdados[i].periodico[xdados[i].qtdPeriodicos].titulo = strncpy(xdados[i].periodico[xdados[i].qtdPeriodicos].titulo, nome, strlen(nome));
            xdados[i].qtdPeriodicos++;
            
        }

    }

}

void setConfNames(char *line,tdados *xdados){


    for (int i = 0; i < QTD_E-1; i++)
    {
        //get the last three characters of the line
        char *lastThree = line + strlen(line) - 3;
        

        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
            xdados[i].conferencia[xdados[i].qtdConferencias].titulo = malloc(sizeof(char)*strlen(nome));    
            xdados[i].conferencia[xdados[i].qtdConferencias].titulo = strncpy(xdados[i].conferencia[xdados[i].qtdConferencias].titulo, nome, strlen(nome));
            xdados[i].qtdConferencias++;
            
        }

    }

}

void addPerToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores){
    turnUpperCase(nome);
    int classificado;
    classificado = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < xdados[i].qtdPeriodicos-1; j++){
            if(strstr( xdados[i].periodico[j].titulo, nome)){
                xdados[i].periodico[j].quantidade++;
                xdados[i].quantidade++;
                xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores].estratos[i]++;
                //printf("%d\n", xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores].estratos[i]);
                classificado = 1;
            }
        }
    }
    if(classificado == 0){
        xdados[9].periodico[xdados[9].qtdPeriodicos].titulo = malloc(sizeof(char)*strlen(nome));
        xdados[9].periodico[xdados[9].qtdPeriodicos].titulo = strncpy(xdados[9].periodico[xdados[9].qtdPeriodicos].titulo, nome, strlen(nome));
        xdados[9].periodico[xdados[9].qtdPeriodicos].quantidade++;
        xdados[9].quantidade++;
        xdados[9].qtdPeriodicos++;
    }
}

void printPeriodicosResumo(tdados *xdados){

    for (int i = 0; i < QTD_E-1; i++)
    {
        printf("Estrato %s:\n", enumName(xdados[i].nome));

        for(int j = 0; j < xdados[i].qtdPeriodicos-1; j++){
            if(xdados[i].periodico[j].quantidade > 0){
                printf("%s: %d\n", xdados[i].periodico[j].titulo, xdados[i].periodico[j].quantidade);
            }    
        }
        
        printf("\n");
    }
    
}

void printNaoClassificados(tdados *xdados){

        printf("Estrato %s:\n", enumName(xdados[9].nome));

        for(int j = 0; j < xdados[9].qtdPeriodicos; j++)
            printf("%s: %d\n", xdados[9].periodico[j].titulo, xdados[9].periodico[j].quantidade);
        
        printf("\n");

    
}

void inicializaStructRes(tpesquisadores *xpesquisadores){ 
    xpesquisadores->qtdPesquisadores = 0;
    xpesquisadores->pesquisador = NULL;
}

void inicializaRes(tpesquisadores *xpesquisadores, char *nome){
    xpesquisadores->pesquisador = realloc(xpesquisadores->pesquisador, sizeof(tpesquisador)*(xpesquisadores->qtdPesquisadores+1+(sizeof(int)*QTD_E)));
    xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores].nome = malloc(sizeof(char)*strlen(nome));
    xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores].nome = strncpy(xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores].nome, nome, strlen(nome));
    
    for(int i=0; i < QTD_E-1; i++){
        xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores].estratos[i] = 0;
    }

    xpesquisadores->qtdPesquisadores++;
}