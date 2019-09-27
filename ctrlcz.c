#include "headers.h"

void bg(char *args[], int n)
{

    if (n != 2)
    {
        fprintf(stderr,"twanshell: kjob: Exactly one argument required\n");
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
                if (kill(pids[i].pid, SIGTTIN) < 0) //whytho
                {
                    perror("Error in kill");
                    return;
                }
                if (kill(pids[i].pid, SIGCONT) < 0)
                {
                    perror("Error in kill");
                    return;
                }

                else
                {
                    flag = 1;
                }
            }
        }
    }

    if (flag == 0)
        fprintf(stderr,"twanshell: No such process\n");
}

void fg(char *args[], int n)
{
    if (n != 2)
    {
        fprintf(stderr,"twanshell: kjob: Exactly one argument required\n");
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
                if (kill(pids[i].pid, SIGCONT) < 0)
                {
                    perror("Error in kill");
                }

                pids[i].status = 0;
                fore.pid = pids[i].pid;
                strcpy(fore.name, pids[i].name);
                fore.status = 1;
                flag = 1;
                actives--;
                
                waitpid(-1, NULL, WUNTRACED);
                break;
            }
        }
    }

    if (flag == 0)
        fprintf(stderr,"twanshell: No background process with given background number\n");
}

// void ctrlzhandler(int sig_num)
// {
//     if (getpid() != shellPID)
//         return;

//     if (fore.status == 1)
//     {
//         printf("pid=%d\n",fore.pid);

//         if (kill(fore.pid, SIGTTIN) < 0)
//         {
//             perror("Error in kill");
//             return;
//         }
//         if (kill(fore.pid, SIGTSTP) < 0)
//         {
//             perror("Error in kill");
//             return;
//         }

//         printf("[%d] %d\n", ++actives, fore.pid);
//         pids[pidcnt].pid = fore.pid;
//         pids[pidcnt].status = 1;
//         strcpy(pids[pidcnt++].name, fore.name);
//         fore.status = 0;
//         //do a pid checker to avoid overflow
//         //return;
//         signal(SIGTSTP, ctrlzhandler);
//     }

//     else
//     {
//         fprintf(stderr,"\ntwanshell: No foreground process\n");
//         tildconvertedpwd();
//         fflush(stdout);
//     }
//     jobs(NULL,1);
    
//     //fflush(stdout);
//     return;
// }

void ctrlzhandler(int sig_num)
{
    if (getpid() != shellPID)
        return;

    if (fore.status == 1)
    {
        if (kill(fore.pid, SIGTTIN) < 0)
        {
            perror("Error in kill");
            return;
        }
        if (kill(fore.pid, SIGTSTP) < 0)
        {
            perror("Error in kill");
            return;
        }

        printf("[%d] %d\n", ++actives, fore.pid);
        pids[pidcnt].pid = fore.pid;
        pids[pidcnt].status = 1;
        strcpy(pids[pidcnt++].name, fore.name);
        fore.status = 0;
        //do a pid checker to avoid overflow

        return;
    }

    signal(SIGTSTP,ctrlzhandler);
}

void ctrlchandler(int sig_num)
{
    if (getpid() != shellPID)
        return;

    if (fore.status == 1)
    {
        if (kill(fore.pid, SIGINT) < 0)
        {
            perror("Error in kill");
            printf("%s",fore.name);
        }
        fore.status = 0;
    }
    else
    {
        fprintf(stderr,"\ntwanshell: No foreground process\n");
        fflush(stdout);
        tildconvertedpwd();
    }
    signal(SIGINT, ctrlchandler);
    
    fflush(stdout);
    return;
}