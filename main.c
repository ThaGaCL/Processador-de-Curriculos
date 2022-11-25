#include "libdir.h"
#include "libutil.h"

int main (int argc, char **argv)
{   
    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;
    tpesquisadores *xpesquisadores = malloc(sizeof(tpesquisadores));

    
    getOptions(argc, argv, &path, &pathCon, &pathPer); // Recebes as informacoes das flags
    
    tdados *xdados = malloc(sizeof(tdados) * QTD_E);
    
    inicializaStructRes(xpesquisadores); // Inicializa a Struct de Pesquisadores
    
    inicializaEstratos(xdados, pathPer, pathCon); // Copia o nome das conferencias e perifericos para dentro da Struct 

    DIR *dirstream = openDir(path); // Abre a pasta de curriculos
    readDir(dirstream, xdados, path, xpesquisadores); // Le a pasta curriculos

    printPeriodicosResumo(xdados); // Imprime o resumo dos periódicos
    printNaoClassificados(xdados); // Imprime os periodicos nao classificados


    freeDados(xdados); // Libera a memoria alocada pela Struct de Dados
    (void) closedir(dirstream);
    
    return 0;

}

