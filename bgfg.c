#include "headers.h"

void child_sig()
{
    pid_t pid;

    int stat;
    pid = waitpid(-1, &stat, WNOHANG|WUNTRACED);

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

                strcpy(pids[i].status,"Exited");
                tildconvertedpwd();
                fflush(stdout);
                actives--;
                break;
            }

            else if (WIFSTOPPED(stat)){
                strcpy(pids[i].status,"Stopped");
            }

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

void backgrnd(char *args[], int n)
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
        printf("Error: Forking failed");
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
            printf("Error: execvp failed"); //if execvp fails do we still want to add to the procs array
        exit(0);
    }
    else
    {
        printf("[%d] %d\n", ++actives, pid);
        pids[pidcnt].pid = pid;
        strcpy(pids[pidcnt].status,"Running");
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