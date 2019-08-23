#include "headers.h"

void child_sig()
{
    pid_t pid;

    int stat;
    pid = waitpid(-1, &stat, WNOHANG);

    for (int i = 0; i < pidcnt; i++)
    {
        if (pid == pids[i].pid)
        {

            int exit_status = WEXITSTATUS(stat);
            if (exit_status == 0)
            {
                fprintf(stderr, "\nProcess %s with pid %d exited normally\n", pids[i].name, pid);
            }
            else
            {
                fprintf(stderr, "\nProcess %s with pid %d exited with exit status %d\n", pids[i].name, pid, exit_status);
            }
            tildconvertedpwd();
            fflush(stdout);
            actives--;
            break;
        }
    }
}

void foregrnd(char *args[]) //change params
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
        printf("twanshell: Error: Forking failed\n");
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
            printf("twanshell: Error: execvp failed\n");
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
        printf("[%d] %d\n", ++actives, pid);
        pids[pidcnt].pid = pid;
        strcpy(pids[pidcnt++].name, args[0]);
    }
}