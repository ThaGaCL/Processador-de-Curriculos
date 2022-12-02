#include "libdir.h"
#include "libutil.h"

int main (int argc, char **argv)
{   
    tdados *xdados = malloc(sizeof(tdados) * QTD_E);
    tpesquisadores *xpesquisadores = malloc(sizeof(tpesquisadores));

    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;

    getOptions(argc, argv, &path, &pathCon, &pathPer); // Recebes as informacoes das flags
    
    int dirSize = getDirSize(path);
    
    inicializaStructRes(xpesquisadores, dirSize); // Inicializa a Struct de Pesquisadores

    inicializaEstratos(xdados, pathPer, pathCon); // Copia o nome das conferencias e perifericos para dentro da Struct 

    DIR *dirstream = openDir(path); // Abre a pasta de curriculos
    readDir(dirstream, xdados, path, xpesquisadores); // Le a pasta curriculos

    printPeriodicosResumo(xdados); // Imprime o resumo dos periódicos
    printConfereciasResumo(xdados); // Imprime o resumo das conferencias
    printNaoClassificados(xdados); // Imprime os periodicos nao classificados
    printResumoRes(xpesquisadores); // Imprime o resumo do pesquisador


    freeDados(xdados); // Libera a memoria alocada pela Struct de Dados
    freeStructRes(xpesquisadores, dirSize); // Libera a memoria alocada pela Struct de Pesquisadores
    (void) closedir(dirstream);
    
    return 0;

}

