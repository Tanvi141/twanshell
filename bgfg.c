#include "headers.h"

void child_sig()
{
    pid_t pid;

    int stat;
    pid = waitpid(-1, &stat, WNOHANG);
    // if (pid < 0)
    //     printf("Error: waitpid failed\n");
        
    for (int i = 0; i < pidcnt; i++)
    {
        if (pid == pids[i].pid)
        {
            int newstat;
            int exit_status = WEXITSTATUS(newstat);
            if (exit_status == 0)
            {
                fprintf(stderr, "Process %s with pid %d exited normally\n",pids[i].name ,pid);
            }
            else
            {
                fprintf(stderr, "Process %s with pid %d exited with exit status %d\n",pids[i].name ,pid, exit_status);
            }
            tildconvertedpwd(tild);
            fflush(stdout);
            break;
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
        exit(0);
    }
    else
    {
        printf("[%d] %d\n",pidcnt,pid);
        pids[pidcnt].pid = pid;
        strcpy(pids[pidcnt++].name, args[0]);
    }
}
