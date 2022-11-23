#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "libutil.h"
#include "libstruct.h"

#define LINESIZE 1024

FILE* openFile(char* filename);

int getSize(FILE* file);

void printFile(FILE* arq, tdados *xdados);

DIR* openDir(char* dirname);

void readDir(DIR* dirstream, tdados *xdados, char* dirname);

void getFileLines(FILE *arq);

int getPerName(tdados *xdados, char *str);

void inicializaEstratos(tdados *xdados, char *pathPer, char *pathCon);

void getPerLines(FILE *arq, tdados *xdados);

void getConfLines(FILE *arq, tdados *xdados);