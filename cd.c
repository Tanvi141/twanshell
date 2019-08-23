#include "headers.h"

void cd(char *args[],int n)
{
    char loc[FILENAME_MAX] = "";

    if (n == 1)  //cd
        strcpy(loc, tild);
    else if (args[1][0] == '~')   //cd ~/[path]
    {

        strcpy(loc, tild);
        strcat(loc, &args[1][1]);
    }

    else  //path relative to current directory or home of computer
        strcpy(loc, args[1]);

    if(n>2) fprintf(stderr,"twanshell: Error: Too many arguments: cd\n");

    else if(chdir(loc)){
        perror("cd");
    }
}