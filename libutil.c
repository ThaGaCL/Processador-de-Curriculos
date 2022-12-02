#include "libutil.h"

// Recebe as informacoes das flags
void getOptions(int argc, char *argv[], char** path, char** pathCon, char** pathPer){
    int option;

    opterr = 0;

    // options:  -a, -b, -c value (defined by "abc:")
    while ((option = getopt(argc, argv, "d:c:p:")) != -1)
        switch (option)
        {
        case 'd': // option -a was set
            *path = optarg;
            break;
        case 'c': // option -b was set
            *pathCon = optarg;
            break;
        case 'p': // option -c was set with value
            *pathPer = optarg;
            break;
        default:
            exit(1);
        }


}

// Transforma uma string em maiuscula
char* turnUpperCase(char *str){

    //make string uppercase
    for (int i = 0; str[i]; i++){
        str[i] = toupper(str[i]);
    }

    return str;
    
}

// Transforma uma string em minuscula
char* turnLowerCase(char *str){

    //make string lowercase
    for (int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }

    return str;
    
}

// Encontra uma tag dentro de uma string e a corta
char *findTagInString(char *str, char *mainTag, char *tag){
    // Copia a string
    char * temp = (char*)malloc(sizeof(char*)*strlen(str));
    strcpy(temp, str);

    char * aux = strstr(temp, mainTag); // Encontra a tag principal
    aux = strstr(aux, tag);   // Encontra a tag secundaria
       
    // Corta o conteudo da tag secundaria e o retorna
    char* token = strtok(aux, "\"");   
    token = strtok(NULL, "\"");
    token = strtok(token, "\"");
    token = strtok(token, "\"");

    return token;
}