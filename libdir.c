#include "libdir.h"

// ----------*---------- MANIPULACAO DE ARQUIVOS ----------*----------

// Abre o arquivo
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

// Processa os arquivos de currículos
int processesResumes(FILE *arq, tdados *xdados, tpesquisadores *xpesquisadores)
{
    if(!arq){
        perror("Erro ao ler arquivo");
        return 0;
    }
    
    int fileSize;
    fileSize = getSize(arq); // Calcula o tamanho do arquivo

    // Tags para identificar os periodicos
    char *mainTagPer = "<DETALHAMENTO-DO-ARTIGO";
    char *tagNomePer = "TITULO-DO-PERIODICO-OU-REVISTA=\"";
    // char *mainTagAnoPer ="<DADOS-BASICOS-DO-ARTIGO";
    // char *tagAnoPer = "ANO-DO-ARTIGO=\"";
    char *nomePer;
    // int anoPer;

    // Tags para identificar as conferencias
    char *mainTagConf = "<TRABALHO-EM-EVENTOS";
    // char *mainTagAnoConf = "<DADOS-BASICOS-DO-TRABALHO";
    // char *tagAnoConf = "ANO-DO-TRABALHO=\"";
    char *tagNomeConf = "NOME-DO-EVENTO=\"";
    char *nomeConf;
    // int anoConf;

    // Tags para identificar o pesquisador
    char *mainTagRes = "<DADOS-GERAIS";
    char *tagNomeRes = "NOME-COMPLETO=\"";

    char *file_content = (char *)malloc(fileSize * sizeof(char)); // Aloca tamanho da string a partir do tamanho do arquivo
    fread(file_content, sizeof(char), fileSize, arq); // Insere o arquivo inteiro na string
    
    char *nome = findTagInString(file_content,mainTagRes, tagNomeRes); // Pega o nome do pesquisador responsavel
    inicializaRes(xpesquisadores, nome);    // Inicializa o pesquisador
    
    char *str = malloc(sizeof(char) * strlen(file_content)); // Copia o conteudo do arquivo para uma string auxiliar
    strcpy(str, file_content);

    printf("Analizando currículo de %s\n", nome);
    printf("Analizado periodicos aguarde...\n");
    // Percorre o arquivo ate o fim enquanto houver periodicos
    while((str=strstr(str, mainTagPer)) != NULL){
        nomePer = findTagInString(str, mainTagPer, tagNomePer);
        str += strlen(mainTagPer);
        addPerToStruct(xdados, nomePer, xpesquisadores);
    }
    
    // Reseta a string auxiliar
    free(str);
    str = (char *)malloc(fileSize * sizeof(char));
    strcpy(str, file_content);

    printf("Analizado conferencias aguarde...\n");
    // Percorre o arquivo ate o fim enquanto houver conferencias
    while((str=strstr(str, mainTagConf)) != NULL){
        nomeConf = findTagInString(str, mainTagConf, tagNomeConf);
        addConfToStruct(xdados, nomeConf, xpesquisadores);
        str += strlen(mainTagConf);
    }

    free(file_content);
    free(str);
    
    xpesquisadores->qtdPesquisadores++; // Incrementa o numero de pesquisadores
    
    return 1;
}

// Copia o nome das conferencias e perifericos para dentro da Struct 
int inicializaEstratos(tdados *xdados, char *pathPer, char *pathCon){
    

    if(!xdados){
       perror("Erro ao inicializar estratos");
       return 0;
    }

    FILE *per = openFile(pathPer);
    FILE *conf = openFile(pathCon);
    int perSize = getSize(per); // Calcula o tamanho do arquivo de perifericos
    int confSize = getSize(conf); // Faz o mesmo pro arquivo de conferencias

    // Inicializa o estratos 
    for (int i = 0; i < QTD_E; i++)
    {
        xdados[i].nome = i;
        xdados[i].quantidade = 0;
        xdados[i].qtdPeriodicos = 0;
        xdados[i].qtdConferencias = 0;
        xdados[i].periodico = malloc(sizeof(pasta) * perSize);
        xdados[i].conferencia = malloc(sizeof(pasta) * confSize);

    }

    
    getPerLines(per, xdados); // Pega as linhas do arquivo de periodicos
    getConfLines(conf, xdados); // Pega as linhas do arquivo de conferencias
    fclose(per);
    fclose(conf);

    return 1;
}

// ----------*----------*----------*----------*----------*----------*----

// ----------* ---------- MANIPULACAO DE DIRETORIOS ----------*----------

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
            processesResumes(arq, xdados, xpesquisadores);

            free(path);
            fclose(arq);
        }
    }
}

// Calcula o tamanho do diretorio
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

// ----------*----------*----------*----------*----------*----------*----

