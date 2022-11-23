#include "libdir.h"
#include "libutil.h"

int main (int argc, char **argv)
{   
    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;

    getOptions(argc, argv, &path, &pathCon, &pathPer);
    
    tdados *xdados = malloc(sizeof(tdados) * QTD_E);
    inicializaEstratos(xdados, pathPer, pathCon);

    DIR *dirstream = openDir(path) ;
    readDir(dirstream, xdados, path);

    free(xdados);
    (void) closedir(dirstream);
    
    return 0;

}

