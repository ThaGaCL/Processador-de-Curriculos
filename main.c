#include "libdir.h"
#include "libutil.h"

int main (int argc, char **argv)
{   
    char *path = NULL;
    char *pathCon = NULL;
    char *pathPer = NULL;

    getOptions(argc, argv, &path, &pathCon, &pathPer);
    

    DIR *dirstream = openDir(path) ;
    readDir(dirstream, path);


    (void) closedir(dirstream);
    
    return 0;

}

