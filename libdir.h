#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libutil.h"
#include "libstruct.h"
 
#define LINESIZE 1024

// ----------*---------- MANIPULACAO DE ARQUIVOS ----------*----------

// Abre o arquivo
FILE* openFile(char* filename);

// Calcula o tamanho do arquivo
int getSize(FILE* file);

// Pega as linhas do arquivo de periodicos
void getPerLines(FILE *arq, tdados *xdados);

// Pega as linhas do arquivo de conferencias
void getConfLines(FILE *arq, tdados *xdados);

// Processa os arquivos de currículos
int processesResumes(FILE* arq, tdados *xdados, tpesquisadores *xpesquisadores);

// Copia o nome das conferencias e perifericos para dentro da Struct 
int inicializaEstratos(tdados *xdados, char *pathPer, char *pathCon);

// ----------*----------*----------*----------*----------*----------*----


// ----------* ---------- MANIPULACAO DE DIRETORIOS ----------*----------

// Abre o diretorio
DIR* openDir(char* dirname);

// Le o diretorio
void readDir(DIR* dirstream, tdados *xdados, char* dirname, tpesquisadores *xpesquisadores);

// Calcula o tamanho do diretorio
int getDirSize(char* path);

// ----------*----------*----------*----------*----------*----------*----
