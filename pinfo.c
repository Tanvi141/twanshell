#include "headers.h"

void pinfo(char *args[], int n)
{
    int id = getpid();
    if (n == 2)
        sscanf(args[1], "%d", &id);
    char stats[FILENAME_MAX];
    char exec[FILENAME_MAX];
    sprintf(stats, "/proc/%d/stat", id);
    sprintf(exec, "/proc/%d/exe", id);
    FILE *fd = fopen(stats, "r");

    if (!fd)
    {
        perror("Error: Process does not exist");
        return;
    }

    else
    {
        char status;
        unsigned long mem;
        fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status, &mem);
        fclose(fd);
        printf("pid -- %d\n", id);
        printf("Process Status -- %c\n", status);
        printf("memory -- %lu\n", mem);
    }

    char path[FILENAME_MAX];
    int t = readlink(exec, path, 1000);
    if (t < 0)
    {
        perror("Error reading the process");
    }
    else
    {
        path[t] = '\0';
        char converted[FILENAME_MAX];
        tildconverter(converted,path);
        printf("Executable Path -- %s\n",converted);
    }
}