#include "libdir.h"

FILE *openFile(char *filename)
{
    FILE *arq = fopen("./curriculos/curriculo.xml", "r");
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
    int fileSize = getSize(arq);
    char line[LINESIZE + 1];

    char *fileContent = (char *)malloc(fileSize * sizeof(char));
    fread(fileContent, sizeof(char), fileSize, arq);

    printf("%s", fileContent);
}

DIR *openDir(char *dirname)
{

    DIR *dirstream = opendir("./curriculos");
    if (!dirstream)
    {
        perror("Couldn't open the directory");
        exit(1);
    }

    return dirstream;
}

void readDir(DIR *dirstream)
{
    struct dirent *direntry;
    char *dirname = "curriculo/";

    for (;;)
    {
        // pega a próxima entrada
        direntry = readdir(dirstream);

        // se for nula, encerra a varredura
        if (!direntry)
            break;

        if (direntry->d_type == DT_REG)
        {

            printf("%s\n", direntry->d_name);
            char *path = malloc(sizeof(direntry->d_name) + sizeof(dirname) + 2);
            path = realpath(path, NULL);
            FILE *arq = openFile(path);
            printFile(arq);

            fclose(arq);
        }
    }
}