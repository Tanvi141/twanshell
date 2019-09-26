#include "headers.h"

void show(char dirname[], int l, int a, int count)
{

    DIR *p;
    struct dirent **files;
    int lim = scandir(dirname, &files, NULL,alphasort);
    if (lim < 0)
    {
        char message[FILENAME_MAX + 30];
        strcpy(message, "ls: cannot access directory ");
        strcat(message, dirname);
        perror(message);
    }

    else
    {
        if (count > 1)
            printf("%s:\n", dirname);

        for (int i = 0; i < lim; i++)
        {
            struct dirent *d = files[i];

            if (a == 0 && d->d_name[0] == '.')
                continue;

            char path[FILENAME_MAX];
            strcpy(path, dirname);
            strcat(path, "/");
            strcat(path, d->d_name);

            struct stat fileStat;
            stat(path, &fileStat);

            if (l == 1)
            {

                printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fileStat.st_nlink);
                struct passwd *pw = getpwuid(fileStat.st_uid);
                struct group *gr = getgrgid(fileStat.st_gid);
                printf(" %s", pw->pw_name);
                printf(" %s", gr->gr_name);
                printf(" %ld", fileStat.st_size);

                char time_str[100] = "";
                time_t now = time(NULL);
                struct tm tmfile, tmnow;
                localtime_r(&fileStat.st_mtime, &tmfile);
                localtime_r(&now, &tmnow);
                if (tmfile.tm_year == tmnow.tm_year)
                {
                    strftime(time_str, sizeof(time_str), "%b %e %H:%M", &tmfile);
                }
                else
                {
                    strftime(time_str, sizeof(time_str), "%b %e  %Y", &tmfile);
                }
                printf(" %s ", time_str);
            }

            printf("%s\n", d->d_name);
        }
    }
}

void ls(char *args[], int n)
{

    int l = 0, a = 0, count = 0; //count keeps track of the number of file arguments

    //setting the flags
    for (int i = 1; i < n; i++)
    {
        if (args[i][0] == '-')
        {
            for (int j = 1; j < strlen(args[i]); j++)
            {
                if (args[i][j] == 'l')
                    l = 1;
                else if (args[i][j] == 'a')
                    a = 1;
                else
                {
                    fprintf(stderr,"twanshell: Only flags 'l' and 'a' recognised\n");
                    return;
                }
            }
        }

        else
            count++; //keeps track of number of arguments
    }

    for (int i = 1; i < n; i++)
    {
        if (args[i][0] != '-')
        {
            char dirname[FILENAME_MAX];

            //replacing the tilda
            if (args[i][0] == '~')
            {
                strcpy(dirname, tild);
                strcat(dirname, &args[i][1]);
            }

            else
            {
                strcpy(dirname, args[i]);
            }

            show(dirname, l, a, count);
        }
    }

    if (count == 0)
        show(".", l, a, count);
}
