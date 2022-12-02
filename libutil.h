#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Recebe as informacoes das flags
void getOptions(int argc, char *argv[], char** path, char** pathCon, char** pathPer);

// Transforma uma string em maiuscula
char* turnUpperCase(char *str);

// Transforma uma string em minuscula
char* turnLowerCase(char *str);

// Encontra uma tag dentro de uma string e a corta
char *findTagInString(char *str, char *mainTag, char *tag);