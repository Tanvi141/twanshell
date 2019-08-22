#include "headers.h"

void child_sig()
{
    pid_t pid;

    int stat;
    pid = waitpid(-1, &stat, WNOHANG);

    for (int i = 0; i < pidcnt; i++)
    {
        if (pid < 0)
            printf("Error: waitpid failed\n");

        int newstat;
        int a = WEXITSTATUS(newstat);
        if (a && pid == pids[i])
        {
            fprintf(stderr, "Process %d exited with exit status %d\n", pid, a);
            tildconvertedpwd(tild);
            fflush(stdout);
        }
    }
    
}

void foregrnd(char *args[]) //change params
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
        printf("Error: Forking failed\n");
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
            printf("Error: execvp failed\n");
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}

void backgrnd(char *args[])
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
        printf("Error: Forking failed");
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
            printf("Error: execvp failed");
        printf("Child ded");
        exit(0);
    }
    else
    {
        printf("[1] %d\n", pid);
        pids[pidcnt++] = pid;
    }
}
