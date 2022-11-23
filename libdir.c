#include "libdir.h"

FILE *openFile(char *filename)
{
    FILE *arq = fopen(filename, "r");
    if (!arq)
    {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    return arq;
}

int getSize(FILE *file)
{

    fseek(file, 0, SEEK_END);

    int size = ftell(file);
    rewind(file);

    return size;
}

void printFile(FILE *arq, tdados *xdados, tpesquisadores *xpesquisadores)
{
    int fileSize;
    fseek(arq, 0, SEEK_END);
    fileSize = ftell(arq);
    rewind(arq);

    char *file_content = (char *)malloc(fileSize * sizeof(char));

    fread(file_content, sizeof(char), fileSize, arq);
 
    getPerName(xdados, file_content, xpesquisadores);
}

DIR *openDir(char *dirname)
{

    DIR *dirstream = opendir(dirname);
    if (!dirstream)
    {
        perror("Couldn't open the directory");
        exit(1);
    }

    return dirstream;
}

void readDir(DIR *dirstream, tdados *xdados, char *dirname, tpesquisadores *xpesquisadores)
{
    struct dirent *direntry;

    for (;;)
    {
        // pega a próxima entrada
        direntry = readdir(dirstream);

        // se for nula, encerra a varredura
        if (!direntry)
            break;

        if (direntry->d_type == DT_REG)
        {

            char *path = malloc(sizeof(direntry->d_name) + sizeof(dirname) + 2);

            path = realpath(dirname, path);
            path = strcat(path, "/");
            path = strcat(path, direntry->d_name);

            FILE *arq = openFile(path);
            printFile(arq, xdados, xpesquisadores);

            fclose(arq);
        }
    }
}

char *getResName(char* str){
 char *tag = "NOME-COMPLETO";
        
        str = strstr(str, tag); // Encontra a tag na string
        char* str3 = strdup(str); // Copia a string
        
        //Separa o token do resto da string 
        char* token = strtok(str3, "\"");    
        token = strtok(NULL, "\"");
        token = strtok(token, "\"");
        token = strtok(token, "\"");

    return token;

}

int getPerName(tdados *xdados, char *str, tpesquisadores *xpesquisadores)
{
    // Returns first token
    char *tag = "DETALHAMENTO-DO-ARTIGO";
    char *str2 = strdup(str);
    char *str3;
    char *nome = getResName(str);
    inicializaRes(xpesquisadores, nome);
    //printf("%s\n", nome);
    // Set str2 offset after tag
    while((str2 = strstr(str2, tag)) != NULL){
        str3 = strdup(str2);
        char* token = strtok(str3, "\"");    
        token = strtok(NULL, "\"");
        token = strtok(token, "\"");
        token = strtok(token, "\"");
        addPerToStruct(xdados, token, xpesquisadores);
        str2 += strlen(tag);
        free(str3);
    }    

    // printf("%d\n", xpesquisador->qtdPesquisadores);
    // xpesquisador->qtdPesquisadores++;
    free(str2);

    return 0;
}


void inicializaEstratos(tdados *xdados, char *pathPer, char *pathCon){
   
    FILE *per = openFile(pathPer);
    FILE *conf = openFile(pathCon);
    int perSize = getSize(per);
    int confSize = getSize(conf);

    for (int i = 0; i < QTD_E; i++)
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

void freeDados(tdados *xdados){
    for (int i = 0; i < QTD_E; i++)
    {
        free(xdados[i].periodico);
        free(xdados[i].conferencia);
    }
    free(xdados);
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

