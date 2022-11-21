#include "libstruct.h"

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
        return ("");
    }
}


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
            xdados[i].qtdPeriodicos++;
            
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
            xdados[i].qtdConferencias++;
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

}

void getConfLines(FILE *arq, tdados *xdados){
    char line[LINESIZE+1];
    
    fgets(line, LINESIZE, arq);
    while(!feof(arq)){
        setConfNames(line, xdados);
        fgets(line, LINESIZE, arq);
        
    }

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


