#include "libdir.h"
#include "libstruct.h"

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

void printFile(FILE *arq)
{
    int fileSize;
    fseek(arq, 0, SEEK_END);
    fileSize = ftell(arq);
    rewind(arq);

    char *file_content = (char *)malloc(fileSize * sizeof(char));

    fread(file_content, sizeof(char), fileSize, arq);
 
    getPerName(file_content);
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

void readDir(DIR *dirstream, char *dirname)
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
            printFile(arq);

            fclose(arq);
        }
    }
}


int getPerName(char *str)
{
    // Returns first token
    char *tag = "DETALHAMENTO-DO-ARTIGO";
    char *str2 = strdup(str);
    char *str3;
    // Set str2 offset after tag

    while((str2 = strstr(str2, tag)) != NULL){
        str3 = strdup(str2);
        char* token = strtok(str3, "\"");    
        token = strtok(NULL, "\"");
        token = strtok(token, "\"");
        token = strtok(token, "\"");
        printf("%s\n", token);
        str2 += strlen(tag);
        free(str3);
    }    

    free(str2);

    return 0;
}

