#include "libdir.h"
#include "libutil.h"

int main (int argc, char **argv)
{   
    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;
    tpesquisadores *xpesquisadores = malloc(sizeof(tpesquisadores));


    getOptions(argc, argv, &path, &pathCon, &pathPer);
    
    tdados *xdados = malloc(sizeof(tdados) * QTD_E);
    
    inicializaStructRes(xpesquisadores);
    
    inicializaEstratos(xdados, pathPer, pathCon);

    DIR *dirstream = openDir(path) ;
    readDir(dirstream, xdados, path, xpesquisadores);

    printPeriodicosResumo(xdados);
    printNaoClassificados(xdados);


    freeDados(xdados);
    (void) closedir(dirstream);
    
    return 0;

}

