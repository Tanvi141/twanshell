#include "headers.h"

void child_sig()
{
    pid_t pid;

    int stat;
    pid = waitpid(-1, &stat, WNOHANG | WUNTRACED);

    for (int i = 0; i < pidcnt; i++)
    {
        if (pid == pids[i].pid)
        {

            if (WIFEXITED(stat))
            {
                int exit_status = WEXITSTATUS(stat);
                if (exit_status == 0)
                {
                    fprintf(stderr, "\rProcess %s with pid %d exited normally\n", pids[i].name, pid);
                }
                else
                {
                    fprintf(stderr, "\rProcess %s with pid %d exited with exit status %d\n", pids[i].name, pid, exit_status);
                }

                pids[i].status = 0;
                tildconvertedpwd();
                fflush(stdout);
                actives--;
                break;
            }
        }
    }
}

void foregrnd(char *args[], int n)
{
    pid_t pid;
    pid = fork();
    setpgid(0, 0);
    if (pid < 0)
        fprintf(stderr, "twanshell: Error: Forking failed\n");
    else if (pid == 0)
    {

        // close(STDIN_FILENO);
        // close(STDOUT_FILENO);
        // close(STDERR_FILENO);

        if (execvp(args[0], args) < 0)
            fprintf(stderr, "twanshell: Error: execvp failed\n");
        printf("here!f\n");
    }
    else
    {
        fore.pid = pid;

        char send[100] = "";
        for (int i = 0; i < n - 1; i++)
        {
            strcat(send, args[i]);
            strcat(send, " ");
        }
        strcat(send, args[n - 1]);
        strcpy(fore.name, send);
        fore.status = 1;
        printf("here!\n");
        waitpid(-1, NULL, WUNTRACED);
        printf("here\n");
    }
}

void backgrnd(char *args[], int n)
{
    pid_t pid;
    pid = fork();
    setpgid(0, 0);
    if (pid < 0)
        fprintf(stderr, "Error: Forking failed");
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
            fprintf(stderr, "Error: execvp failed"); //if execvp fails do we still want to add to the procs array
        exit(0);
    }
    else
    {
        printf("[%d] %d\n", ++actives, pid);
        pids[pidcnt].pid = pid;
        pids[pidcnt].status = 1;
        char send[100] = "";
        for (int i = 0; i < n - 1; i++)
        {
            strcat(send, args[i]);
            strcat(send, " ");
        }

        strcat(send, args[n - 1]);

        strcpy(pids[pidcnt++].name, send);
        //do a pid checker to avoid overflow
    }

    //getting messed up in firefox &
}