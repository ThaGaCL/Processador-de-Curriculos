#include "libutil.h"

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

char* turnUpperCase(char *str){

    //make string uppercase
    for (int i = 0; str[i]; i++){
        str[i] = toupper(str[i]);
    }

    return str;
    
}