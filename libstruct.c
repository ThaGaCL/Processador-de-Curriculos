#include "libstruct.h"


void printPer(tdados *xdados){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j <= xdados[i].qtdPeriodicos-1; j++){
             printf("%s\n", xdados[i].periodico[j].titulo);
        }
    }
}

void printConf(tdados *xdados){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j <= xdados[i].qtdConferencias-1; j++){
             printf("%s\n", xdados[i].conferencia[j].titulo);
        }
    }
}


void setPerNames(char *line,tdados *xdados){


    for (int i = 0; i < 9; i++)
    {
        //get the last three characters of the line
        char *lastThree = line + strlen(line) - 3;
        

        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
            xdados[i].periodico[xdados[i].qtdPeriodicos].titulo = malloc(sizeof(char)*strlen(nome));    
            xdados[i].periodico[xdados[i].qtdPeriodicos].titulo = strncpy(xdados[i].periodico[xdados[i].qtdPeriodicos].titulo, nome, strlen(nome));
           //printf("%s\n", xdados[i].periodico[xdados[i].qtdPeriodicos].titulo);
            xdados[i].qtdPeriodicos++;
            
            //xdados->periodico[xdados->qtdPeriodicos].titulo recebe o nome    
        }

    }

}

void setConfNames(char *line,tdados *xdados){


    for (int i = 0; i < 9; i++)
    {
        //get the last three characters of the line
        char *lastThree = line + strlen(line) - 3;
        

        if(strstr(lastThree,enumName(xdados[i].nome))){
            
            char *nome = malloc(sizeof(char)*strlen(line));
            nome = strncpy(nome,line, (strlen(line)-strlen(enumName(xdados[i].nome))-1));
            xdados[i].conferencia[xdados[i].qtdConferencias].titulo = malloc(sizeof(char)*strlen(nome));    
            xdados[i].conferencia[xdados[i].qtdConferencias].titulo = strncpy(xdados[i].conferencia[xdados[i].qtdConferencias].titulo, nome, strlen(nome));
           //printf("%s\n", xdados[i].periodico[xdados[i].qtdPeriodicos].titulo);
            printf("%s\n", xdados[i].conferencia[xdados[i].qtdConferencias].titulo);
            xdados[i].qtdConferencias++;
            //xdados->periodico[xdados->qtdPeriodicos].titulo recebe o nome    
        }

    }

}

void getPerLines(FILE *arq, tdados *xdados){
    char line[LINESIZE+1];
    
    fgets(line, LINESIZE, arq);
    while(!feof(arq)){
        setPerNames(line, xdados);
        fgets(line, LINESIZE, arq);
        
    }

    //printPer(xdados);

}

void getConfLines(FILE *arq, tdados *xdados){
    char line[LINESIZE+1];
    
    fgets(line, LINESIZE, arq);
    while(!feof(arq)){
        setConfNames(line, xdados);
        fgets(line, LINESIZE, arq);
        
    }

    // printConf(xdados);

}

void inicializaEstratos(tdados *xdados){
   
    char* pathper = "qualis-periodicos.txt";
    char* pathconf = "qualis-conf.txt";
    FILE *per = openFile(pathper);
    FILE *conf = openFile(pathconf);
    int perSize = getSize(per);
    int confSize = getSize(conf);

    for (int i = 0; i < 9; i++)
    {
        xdados[i].nome = i;
        xdados[i].quantidade = 0;
        xdados[i].qtdPeriodicos = 0;
        xdados[i].periodico = malloc(sizeof(pasta) * perSize);
        xdados[i].conferencia = malloc(sizeof(pasta) * confSize);

    }

    
    getPerLines(per, xdados);
    getConfLines(conf, xdados);
    fclose(per);
    fclose(conf);

}


