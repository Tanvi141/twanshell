#include "headers.h"

void cd(char *args[], char tild[],int n)
{
    // need to take care of error handling for chdir
    //also need only one argument
    if(n<2) chdir(tild);
    else if (args[1][0] == '~')
    {
        char loc[FILENAME_MAX];
        strcpy(loc, tild);
        strcat(loc, &args[1][1]);
        chdir(loc);
    }
    else
        chdir(args[1]);   //just cd should go to tilda
    //need to implement cd ~/..
}