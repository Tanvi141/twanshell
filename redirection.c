#include "headers.h"

void redirect(char word[], char ops[5][5], int num) //spaces in redirect
{
    while (word[strlen(word) - 1] == '\n') //removes any trailing \n
        word[strlen(word) - 1] = '\0';

    char files[5][10000];
    int index = 0;
    int j = num;
    for (int i = strlen(word); i >= 0; i--)
    {
        if (word[i] == '<' || word[i] == '>')
        {
            if (i + 1 < strlen(word) && word[i + 1] != '\0')
                strcpy(files[j--], &word[i + 1]);
            word[i] = '\0';
        }
    }
    strcpy(files[0], word);

    int in, out;
    pid_t pid = fork(); //pid<0 case

    if (pid < 0)
        fprintf(stderr, "Error in forking");
    else if (pid == 0)
    {
        for (int i = 0; i < num; i++)
        {
            //remove spaces in front
            int temp = 0;
            while (files[i + 1][temp] == ' ')
                temp++;
            for (int j = temp; j < strlen(files[i + 1])+1; j++)
            {
                files[i + 1][j - temp] = files[i + 1][j];
            }

            //remove trailing whilespaces
            while (files[i+1][strlen(word) - 1] == ' ') 
                files[i+1][strlen(word) - 1] = '\0';

            if (strcmp(ops[i], "<") == 0)
            {
                in = open(files[i + 1], O_RDONLY);
                if (in < 0)
                {
                    fprintf(stderr, "Error opening file !%s!\n", files[i + 1]);
                    exit(0);
                }

                else
                {
                    dup2(in, 0);
                    close(in);
                }
            }

            else
            {
                if (strcmp(ops[i], ">") == 0)
                    out = open(files[i + 1], O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                else
                    out = open(files[i + 1], O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);

                if (out < 0)
                {
                    fprintf(stderr, "Error opening file !%s!", files[i + 1]);
                    exit(0);
                }

                else
                {
                    dup2(out, 1);
                    close(out);
                }
            }
        }
        execbuiltin(files[0]);
        exit(0);
    }

    else
    {
        int status;
        while (wait(&status) != pid) //??????????????????????????
            ;
    }
}