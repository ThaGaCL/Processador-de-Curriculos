#include "libdir.h"
#include "libutil.h"
#include "libstruct.h"

int main (int argc, char **argv)
{   
    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;

    getOptions(argc, argv, &path, &pathCon, &pathPer);
    
    tdados *xdados = malloc(sizeof(tdados) * QTD_E);
    inicializaEstratos(xdados);

    DIR *dirstream = openDir(path) ;
    readDir(dirstream, path);


    free(xdados);
    (void) closedir(dirstream);
    
    return 0;

}

