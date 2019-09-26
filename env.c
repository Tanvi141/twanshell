#include "headers.h"

//how to test this???????
void senv(char *args[], int n)
{

    if (n == 2)
    {
        if (setenv(args[1], "", 1) < 0)
            perror("Error in setenv");
    }

    else if (n == 3)
    {
        if (setenv(args[1], args[2], 1) < 0)
            perror("Error in setenv");
    }

    else if (n == 1)
        fprintf(stderr,"twanshell: setenv: Too few arguments\n");

    else
        fprintf(stderr,"twanshell: setenv: Too many arguments");
}

void unsenv(char *args[], int n)
{
    //take arbitrary number of arguments but more than one

    if (n == 1)
        fprintf(stderr,"twanshell: unsetenv: Too few arguments\n");

    else
    {
        for (int i = 1; i < n; i++)
        {
            if (unsetenv(args[i]) < 0)
                perror("Error in unsetenv");
        }
    }
}