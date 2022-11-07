#include "libdir.h"

int main ()
{   
    DIR *dirstream = openDir("./curriculos") ;
    readDir(dirstream);


    (void) closedir(dirstream);
    
    return 0;

}

