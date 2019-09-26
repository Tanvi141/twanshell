#include "headers.h"

void jobs(char *args[], int n)
{
    //what does stopped mean?

    if (n > 1)
        fprintf(stderr,"twanshell: jobs: Too many arguments");

    int index = 0;
    for (int i = 0; i < pidcnt; i++)
    {
        if (pids[i].status == 1)
        {
            index++;

            char stats[FILENAME_MAX];
            sprintf(stats, "/proc/%d/stat", pids[i].pid);
            FILE *fd = fopen(stats, "r");

            if (!fd)
            {
                pids[i].status = 0;
            }

            else
            {
                char statchar;
                unsigned long mem;
                fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &statchar, &mem);
                fclose(fd);
                char state[100] = "Running";
                if (statchar == 'T' || statchar == 't')
                    strcpy(state, "Stopped");
                // else if (statchar == 'R')
                //     strcpy(state, "Running");

                printf("[%d] %s %s[%d]%c\n", index, state, pids[i].name, pids[i].pid, statchar);
            }
        }
    }
}

void overkill(char *args[], int n)
{

    if (n > 1)
    {
       fprintf(stderr,"twanshell: jobs: Too many arguments");
        return;
    }

    for (int i = 0; i < pidcnt; i++)
    {
        if (pids[i].status == 1)
        {

            if (kill(pids[i].pid, SIGKILL) < 0)
            {
                perror("Error in kill");
            }

            else
            {
                pids[i].status = 0;
                actives--;
            }
        }
    }
}

void kjob(char *args[], int n)
{

    if (n != 3)
    {
        fprintf(stderr,"twanshell: kjob: Exactly two arguments required\n");
        return;
    }

    int index = 0, flag = 0;
    for (int i = 0; i < pidcnt; i++)
    {
        if (pids[i].status == 1)
        {
            index++;
            if (index == atol(args[1]))
            {
                if (kill(pids[i].pid, atol(args[2])) < 0)
                {
                    perror("Error in kill");
                    return;
                }

                else
                {
                    flag = 1;
                    pids[i].status = 0;
                    actives--;
                }
                break;
            }
        }
    }

    if (flag == 0)
        fprintf(stderr,"twanshell: No such process\n");
}
