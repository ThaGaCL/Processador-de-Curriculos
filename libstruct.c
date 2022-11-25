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

// Imprime os periodicos presentes na Struct de Dados
void printPer(tdados *xdados){
    for(int i = 0; i < QTD_E; i++){
        for(int j = 0; j <= xdados[i].qtdPeriodicos-1; j++){
             printf("%s\n", xdados[i].periodico[j].titulo);
        }
    }
}

// Imprime as conferencias presentes na Struct de Dados
void printConf(tdados *xdados){
    for(int i = 0; i < QTD_E; i++){
        for(int j = 0; j <= xdados[i].qtdConferencias-1; j++){
             printf("%s\n", xdados[i].conferencia[j].titulo);
        }
    }
}

// Insere o nome do periocico na Struct de Dados
void setPerNames(char *line,tdados *xdados){


    for (int i = 0; i < QTD_E-1; i++)
    {

        char *lastThree = line + strlen(line) - 3; // Pega os tres ultimos char da string para descobrir a classificacao
                                                
        // Checa a qual estrato o periodico pertence                                              
        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            // Insere o nome do periodico na Struct de Dados
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
            xdados[i].periodico[xdados[i].qtdPeriodicos].titulo = malloc(sizeof(char)*strlen(nome));    
            xdados[i].periodico[xdados[i].qtdPeriodicos].titulo = strncpy(xdados[i].periodico[xdados[i].qtdPeriodicos].titulo, nome, strlen(nome));
            xdados[i].qtdPeriodicos++;
            
        }

    }

}

// Insere o nome da conferencia na Struct de Dados
void setConfNames(char *line,tdados *xdados){


    for (int i = 0; i < QTD_E-1; i++)
    {

        char *lastThree = line + strlen(line) - 3; // Pega os tres ultimos char da string para descobrir a classificacao
        
        // Checa a qual estrato a conferencia pertence                                              
        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            // Insere o nome da conferencia na Struct de Dados
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
            xdados[i].conferencia[xdados[i].qtdConferencias].titulo = malloc(sizeof(char)*strlen(nome));    
            xdados[i].conferencia[xdados[i].qtdConferencias].titulo = strncpy(xdados[i].conferencia[xdados[i].qtdConferencias].titulo, nome, strlen(nome));
            xdados[i].qtdConferencias++;
            
        }

    }

}

// Insere os periodicos do curriculo na Struct de Dados
void addPerToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores){
    turnUpperCase(nome); // Modifica a string nome para que fique no maiusculo
    int classificado;
    classificado = 0; // Diz se o periodico foi classificado entre os estratos

    for (int i = 0; i < QTD_E; i++)
    {
        for (int j = 0; j < xdados[i].qtdPeriodicos; j++){
            // Para cada periodico na Struct de Dados checa se o que esta no curriculo foi classificado
            if(strstr( xdados[i].periodico[j].titulo, nome)){
                xdados[i].periodico[j].quantidade++;
                xdados[i].quantidade++;
                classificado = 1;
            }
        }
    }
    // Se o periodico nao foi classificado, o classifica como NC (Nao Classificado)
    if(classificado == 0){
        xdados[9].periodico[xdados[9].qtdPeriodicos].titulo = malloc(sizeof(char)*strlen(nome));
        xdados[9].periodico[xdados[9].qtdPeriodicos].titulo = strncpy(xdados[9].periodico[xdados[9].qtdPeriodicos].titulo, nome, strlen(nome));
        xdados[9].periodico[xdados[9].qtdPeriodicos].quantidade++;
        xdados[9].quantidade++;
        xdados[9].qtdPeriodicos++;
    }
}

// Imprime o Resumo dos Periodicos
void printPeriodicosResumo(tdados *xdados){

    for (int i = 0; i < QTD_E-1; i++)
    {
        printf("Estrato %s:\n", enumName(xdados[i].nome));

        for(int j = 0; j < xdados[i].qtdPeriodicos; j++){
            if(xdados[i].periodico[j].quantidade > 0){
                printf("%s: %d\n", xdados[i].periodico[j].titulo, xdados[i].periodico[j].quantidade);
            }    
        }
        
        printf("\n");
    }
    
}

// Imprime o Resumo dos Periodicos NC
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