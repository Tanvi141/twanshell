#include "headers.h"

void redirect(char word[], char ops[5][5], int num) //spaces in redirect
{
    char *files[5];
    int index = 0;

    files[index] = strtok(word, ops[0]);
    while (files[index] != NULL)
    {
        if (files[index][strlen(files[index]) - 1] == '\n')
            files[index][strlen(files[index]) - 1] = '\0';
        index++;
        files[index] = strtok(NULL, ops[index]);
    }

    int in, out;
    pid_t pid = fork(); //pid<0 case

    if (pid == 0)
    {
        if (strcmp(ops[0], "<") == 0)
        {
            in = open(files[1], O_RDONLY);
            if (in < 0)
            {
                printf("Error opening file");
            }

            else
            {
                dup2(in, 0);
                close(in);
            }
        }

        else
        {
            if (strcmp(ops[0], ">") == 0)
                out = open(files[1], O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            else
                out = open(files[1], O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);

            if (out < 0)
            {
                printf("Error opening file");
            }

            else
            {
                dup2(out, 1);
                close(out);
            }
        }

        execbuiltin(files[0]);
        exit(0);
    }

    else
    {
        int status;
        while (wait(&status) != pid);
    }
}