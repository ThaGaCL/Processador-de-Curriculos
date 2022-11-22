#include "libdir.h"
#include "libutil.h"
#include "libstruct.h"


int main (int argc, char **argv)
{   
    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;
    char *tag1 = "DETALHAMENTO-DO-ARTIGO";

    getOptions(argc, argv, &path, &pathCon, &pathPer);
    
    printf("path: %s pathCon: %s pathPer: %s\n", path, pathCon, pathPer);
    tdados *xdados = malloc(sizeof(tdados) * QTD_E);
    inicializaEstratos(xdados, pathCon, pathPer);

    DIR *dirstream = openDir(path) ;
    readDir(dirstream, path);

    free(xdados);
    (void) closedir(dirstream);
    
    return 0;

}

