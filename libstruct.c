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


// ----------* ---------- FUNCOES DA STRUCT DE DADOS ----------*----------

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
            
            free(nome);
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

            free(nome);
        }

    }

}

// Insere os periodicos do curriculo na Struct de Dados
int addPerToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores){
    turnUpperCase(nome); // Modifica a string nome para que fique no maiusculo
    int classificado;
    classificado = 0; // Diz se o periodico foi classificado entre os estratos

    if(!nome){
        perror("Nome Invalido");
        return 1;
    }

    for (int i = 0; i < QTD_E; i++)
    {
        for (int j = 0; j < xdados[i].qtdPeriodicos; j++){
            // Para cada periodico na Struct de Dados checa se o que esta no curriculo foi classificado
            if(!editDistanceBool(xdados[i].periodico[j].titulo, nome)){
                xdados[i].periodico[j].quantidade++;
                xdados[i].quantidade++;
                xpesquisadores->estratosPer[xpesquisadores->qtdPesquisadores][i]++;
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
        xpesquisadores->estratosPer[xpesquisadores->qtdPesquisadores][9]++;
        xdados[9].qtdPeriodicos++;
    }

    return 0;
}

// Insere os periodicos do curriculo na Struct de Dados
int addConfToStruct(tdados *xdados, char *nome, tpesquisadores *xpesquisadores){

    int classificado;
    classificado = 0; // Diz se o periodico foi classificado entre os estratos

    if(!nome){
        perror("Nome Invalido");
        return 1;
    }

    for (int i = 0; i < QTD_E; i++)
    {
        for (int j = 0; j < xdados[i].qtdConferencias; j++){
            // Para cada periodico na Struct de Dados checa se o que esta no curriculo foi classificado
            if(!editDistanceBool(xdados[i].conferencia[j].titulo, nome)){
                xdados[i].conferencia[j].quantidade++;
                xdados[i].quantidade++;
                xpesquisadores->estratosConf[xpesquisadores->qtdPesquisadores][i]++;
                classificado = 1;
            }

        }
    }
    // Se o periodico nao foi classificado, o classifica como NC (Nao Classificado)
    if(classificado == 0){
        xdados[9].conferencia[xdados[9].qtdConferencias].titulo = malloc(sizeof(char)*strlen(nome));
        xdados[9].conferencia[xdados[9].qtdConferencias].titulo = strncpy(xdados[9].conferencia[xdados[9].qtdConferencias].titulo, nome, strlen(nome));
        xdados[9].conferencia[xdados[9].qtdConferencias].quantidade++;
        xdados[9].quantidade++;
        xpesquisadores->estratosConf[xpesquisadores->qtdPesquisadores][9]++;
        xdados[9].qtdConferencias++;
    }

    return 0;
}

// Libera a memoria alocada pela Struct de Dados
void freeDados(tdados *xdados){
    for (int i = 0; i < QTD_E; i++)
    {
        for(int j = 0; j <= xdados[j].qtdPeriodicos; j++)
            free(xdados[i].periodico[j].titulo);
        
        for(int k = 0; k <= xdados[k].qtdConferencias; k++)
            free(xdados[i].conferencia[k].titulo);

        free(xdados[i].periodico);
        free(xdados[i].conferencia);
    }
    free(xdados);
}


// ----------*----------*----------*----------*----------*----------*----------

// ----------* ---------- FUNCOES DA STRUCT DE PESQUISADORES ----------*----------

// Inicializa a Struct de Pesquisadores
int inicializaStructRes(tpesquisadores *xpesquisadores, int dirSize){
    if(!xpesquisadores){
        perror("Struct de Pesquisadores Invalida");
        return 1;
    }

    xpesquisadores->qtdPesquisadores = 0;
    
    xpesquisadores->estratosPer = (int **)malloc(dirSize * sizeof(int *));
    xpesquisadores->estratosConf = (int **)malloc(dirSize * sizeof(int *));

    for(int i = 0; i < dirSize; i++){
        xpesquisadores->estratosPer[i] = (int *)malloc(QTD_E * sizeof(int));
        xpesquisadores->estratosConf[i] = (int *)malloc(QTD_E * sizeof(int));
    }
    
    for(int i = 0; i < dirSize; i++){
        
        for(int j = 0; j < QTD_E; j++){
            xpesquisadores->estratosPer[i][j] = 0;
            xpesquisadores->estratosConf[i][j] = 0;
        }
        
    }

    return 0;

}

// Inicializa um Pesquisador
int inicializaRes(tpesquisadores *xpesquisadores, char *nome){
    
    if(!xpesquisadores){
        perror("Struct de Pesquisadores Invalida");
        return 1;
    }
    //inicializa vetor pesquisador
    xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores] = malloc(sizeof(char)*strlen(nome));
    xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores] = strncpy(xpesquisadores->pesquisador[xpesquisadores->qtdPesquisadores], nome, strlen(nome));
    
    return 0;
}

void freeStructRes(tpesquisadores *xpesquisadores, int dirSize){
    for(int i = 0; i < dirSize; i++){
        free(xpesquisadores->estratosPer[i]);
        free(xpesquisadores->estratosConf[i]);
    }

    for(int j = 0; j < xpesquisadores->qtdPesquisadores; j++)
        free(xpesquisadores->pesquisador[j]);

    free(xpesquisadores->estratosPer);
    free(xpesquisadores->estratosConf);
}

// ----------*----------*----------*----------*----------*----------*----------

// ----------* ---------- FUNCOES DE IMPRESSAO ----------*----------

// Imprime o Resumo dos Periodicos
void printPeriodicosResumo(tdados *xdados){
    printf("*---------- RESUMO DOS PERIÓDICOS ----------*\n\n");
    int cont;
    for (int i = 0; i < QTD_E-1; i++)
    {
        cont = 0;
        printf("Estrato %s:\n", enumName(xdados[i].nome));

        for(int j = 0; j < xdados[i].qtdPeriodicos; j++){
            if(xdados[i].periodico[j].quantidade > 0){
                printf("%s: %d\n", xdados[i].periodico[j].titulo, xdados[i].periodico[j].quantidade);
                cont++;
            }
        }
        
        if(cont == 0)
            printf("Nenhum Periodico Classificado\n");

        printf("\n");
    }
    
}

void printConfereciasResumo(tdados *xdados){
    int cont;
    printf("*---------- RESUMO DAS CONFERENCIAS POR ESTRATOS ----------*\n\n");
    for (int i = 0; i < QTD_E-1; i++)
    {
        cont = 0;
        printf("Estrato %s:\n", enumName(xdados[i].nome));

        for(int j = 0; j < xdados[i].qtdConferencias; j++){
            if(xdados[i].conferencia[j].quantidade > 0){
                printf("%s: %d\n", xdados[i].conferencia[j].titulo, xdados[i].conferencia[j].quantidade);
            }    
        }

        if(cont == 0)
            printf("Nenhum Periodico Classificado\n");

        printf("\n");
    }
    
}

// Imprime o Resumo dos Periodicos NC
void printNaoClassificados(tdados *xdados){
        printf("*----------RESUMO DOS NAO CLASSIFICADOS ----------*\n\n");
        printf("Estrato %s:\n", enumName(xdados[9].nome));

        for(int j = 0; j < xdados[9].qtdPeriodicos; j++)
            printf("%s: %d\n", xdados[9].periodico[j].titulo, xdados[9].periodico[j].quantidade);
        
        printf("\n");

    
}

// Imprime o resumo dos Pesquisadores   
void printResumoRes(tpesquisadores *xpesquisadores){
    printf("*---------- RESUMO DOS PESQUISADORES POR ESTRATOS ----------*\n\n");
    for(int i = 0; i < xpesquisadores->qtdPesquisadores; i++){
        printf("Pesquisador: %s\n", xpesquisadores->pesquisador[i]);
        printf("+------------+------------+\n|Conferencias| Periódicos |\n+------------+------------+\n");
        
        for(int j = 0; j < QTD_E-2; j++){

            if((xpesquisadores->estratosConf[i][j] < 10)&&(xpesquisadores->estratosPer[i][j] < 10))
                printf("| %s: %d      |   %s: %d    |\n", enumName(j), xpesquisadores->estratosConf[i][j], enumName(j), xpesquisadores->estratosPer[i][j]);
            else if(xpesquisadores->estratosConf[i][j] >= 10)
                printf("| %s: %d     |   %s: %d    |\n", enumName(j), xpesquisadores->estratosConf[i][j], enumName(j), xpesquisadores->estratosPer[i][j]);  
            else
                printf("| %s: %d      |   %s: %d   |\n", enumName(j), xpesquisadores->estratosConf[i][j], enumName(j), xpesquisadores->estratosPer[i][j]);
        }

        printf("| %s: %d       |   %s: %d     |\n", enumName(8), xpesquisadores->estratosConf[i][8], enumName(8), xpesquisadores->estratosPer[i][8]);
        printf("+------------+------------+\n");
        printf("\n");
    }
}

// ----------*----------*----------*----------*----------*----------