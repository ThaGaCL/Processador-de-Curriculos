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

// Calcula o tamanho do arquivo
int getSize(FILE *file)
{

    fseek(file, 0, SEEK_END); // Vai ate o final do arquivo

    int size = ftell(file); // Pega o tamanho do arquivo
    rewind(file); // Volta o ponteiro para o comeco do arquivo

    return size;
}

void printFile(FILE *arq, tdados *xdados, tpesquisadores *xpesquisadores)
{
    int fileSize;
    fileSize = getSize(arq); // Calcula o tamanho do arquivo

    char *file_content = (char *)malloc(fileSize * sizeof(char)); // Aloca tamanho da string a partir do tamanho do arquivo
    fread(file_content, sizeof(char), fileSize, arq); // Insere o arquivo inteiro na string
    
    char *nome = getResName(file_content); // Pega o nome do pesquisador responsavel
    inicializaRes(xpesquisadores, nome);    // Inicializa o pesquisador


    getPerName(xdados, file_content, xpesquisadores, nome); // Pega o nome dos periodicos presentes no arquivo e os insere no local correto
    
    xpesquisadores->qtdPesquisadores++; // Incrementa o numero de pesquisadores
}

// Abre o diretorio
DIR *openDir(char *dirname)
{

    DIR *dirstream = opendir(dirname);
    
    // Checa se o diretorio foi aberto
    if (!dirstream)
    {
        perror("Couldn't open the directory");
        exit(1);
    }

    return dirstream;
}

// Le o diretorio
void readDir(DIR *dirstream, tdados *xdados, char *dirname, tpesquisadores *xpesquisadores)
{
    struct dirent *direntry;

    for (;;)
    {
        // Pega a próxima entrada
        direntry = readdir(dirstream);

        // Se for nula, encerra a varredura
        if (!direntry)
            break;

        // Checa se e um arquivo (no caso sera um .xml)
        if (direntry->d_type == DT_REG)
        {

            char *path = malloc(sizeof(direntry->d_name) + sizeof(dirname) + 2);

            // Pega o caminho do arquivo
            path = realpath(dirname, path);
            path = strcat(path, "/");
            path = strcat(path, direntry->d_name);

            FILE *arq = openFile(path); // Abre o arquivo
            
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

// Pega o nome dos periodicos presentes no arquivo e os insere no local correto
int getPerName(tdados *xdados, char *str, tpesquisadores *xpesquisadores, char *nome)
{
    char *tagPer1 = "DETALHAMENTO-DO-ARTIGO"; 
    char *str2 = strdup(str); // Duplica a string 
    char *str3;


    // Enquanto a tag se repetir no arquivo repete
    while((str2 = strstr(str2, tagPer1)) != NULL){
        str3 = strdup(str2); // Duplica a string 2 (para que ela nao seja alterada)
        // Separa o nome do artigo do resto da string
        char* token = strtok(str3, "\"");   
        token = strtok(NULL, "\"");
        token = strtok(token, "\"");
        token = strtok(token, "\"");
        
        addPerToStruct(xdados, token, xpesquisadores); // Insere o periodico na Struct de Dados
        str2 += strlen(tagPer1);    // Avança a string 2 a frente do ultimo tag encontrado
        free(str3); // Libera a memoria alocada para duplicar a string 2
    }

    
    free(str2); // Libera a memoria alocada para duplicar a string

    return 0;
}

// Copia o nome das conferencias e perifericos para dentro da Struct 
void inicializaEstratos(tdados *xdados, char *pathPer, char *pathCon){
   
    FILE *per = openFile(pathPer);
    FILE *conf = openFile(pathCon);
    int perSize = getSize(per); // Calcula o tamanho do arquivo de perifericos
    int confSize = getSize(conf); // Faz o mesmo pro arquivo de conferencias

    for (int i = 0; i < QTD_E; i++)
    {
        xdados[i].nome = i;
        xdados[i].quantidade = 0;
        xdados[i].qtdPeriodicos = 0;
        xdados[i].periodico = malloc(sizeof(pasta) * perSize);
        xdados[i].conferencia = malloc(sizeof(pasta) * confSize);

    }

    
    getPerLines(per, xdados); // Pega as linhas do arquivo de periodicos
    getConfLines(conf, xdados); // Pega as linhas do arquivo de conferencias
    fclose(per);
    fclose(conf);

}

// Libera a memoria alocada pela Struct de Dados
void freeDados(tdados *xdados){
    for (int i = 0; i < QTD_E; i++)
    {
        free(xdados[i].periodico);
        free(xdados[i].conferencia);
    }
    free(xdados);
}

// Pega as linhas do arquivo de periodicos
void getPerLines(FILE *arq, tdados *xdados){
    char line[LINESIZE+1];
    
    fgets(line, LINESIZE, arq);

    // Percorre o arquivo até o fim
    while(!feof(arq)){
        setPerNames(line, xdados); // Insere o nome do periocico na Struct de Dados
        fgets(line, LINESIZE, arq); // Tenta pegar a proxima linha
    }

}

// Pega as linhas do arquivo de conferencias
void getConfLines(FILE *arq, tdados *xdados){
    char line[LINESIZE+1];
    
    fgets(line, LINESIZE, arq);
    
    // Percorre o arquivo até o fim
    while(!feof(arq)){
        setConfNames(line, xdados); // Insere o nome da conferencia na Struct de Dados
        fgets(line, LINESIZE, arq); // Tenta pegar a proxima linha
        
    }

}

int getDirSize(char* path){
    //get how many files are in directory[

    DIR *dir = openDir(path);
    struct dirent *dirent;
    int count = 0;
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_type == DT_REG) {
            count++;
        }
    }
    rewinddir(dir);
    (void)closedir(dir);
    return count;
}
