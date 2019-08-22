#include "headers.h"

void show(char dirname[], int l, int a, int count)
{
    //printf("dirname=%s\n", dirname);
    DIR *p;
    p = opendir(dirname);
    if (p == NULL)
    {
        perror("ls: cannot access directory"); //try to print dirname here
    }

    else
    {
        if (count > 1)
            printf("%s:\n", dirname);
        struct dirent *d;
        while (d = readdir(p))
        {
            if (a == 0 && d->d_name[0] == '.')
                continue;

            struct stat fileStat;
            stat(d->d_name, &fileStat);

            if (l == 1)
            {
                printf((S_ISDIR(fileStat.st_mode)) ? "d" : "~");
                printf((fileStat.st_mode & S_IRUSR) ? "r" : "~");
                printf((fileStat.st_mode & S_IWUSR) ? "w" : "~");
                printf((fileStat.st_mode & S_IXUSR) ? "x" : "~");
                printf((fileStat.st_mode & S_IRGRP) ? "r" : "~");
                printf((fileStat.st_mode & S_IWGRP) ? "w" : "~");
                printf((fileStat.st_mode & S_IXGRP) ? "x" : "~");
                printf((fileStat.st_mode & S_IROTH) ? "r" : "~");
                printf((fileStat.st_mode & S_IWOTH) ? "w" : "~");
                printf((fileStat.st_mode & S_IXOTH) ? "x" : "~");
                printf(" %ld", fileStat.st_nlink);
                struct passwd *pw = getpwuid(fileStat.st_uid); //pw=0 if error
                struct group *gr = getgrgid(fileStat.st_gid);
                printf(" %s", pw->pw_name);
                printf(" %s", gr->gr_name);
                printf(" %ld", fileStat.st_size);

                char time_str[64] = "";
                time_t now = time(NULL);
                struct tm tmfile, tmnow;
                localtime_r(&fileStat.st_mtime, &tmfile); 
                localtime_r(&now, &tmnow);               
                if (tmfile.tm_year == tmnow.tm_year)
                {   
                    strftime(time_str, sizeof(time_str), "%b %e %H:%M",&tmfile); 
                }
                else
                { 
                    strftime(time_str, sizeof(time_str), "%b %e  %Y",&tmfile);
                }
                printf(" %s ",time_str);

            }
            printf("%s\n", d->d_name);
        }
    }
}

void ls(char *args[], int n, char tild[])
{

    int l = 0, a = 0, count = 0; //count keeps track of the number of file arguments
    //setting the flags
    for (int i = 1; i < n; i++)
    {
        if (args[i][0] == '-')
        {
            for (int j = 0; j < strlen(args[i]); j++)
            {
                if (args[i][j] == 'l')
                    l = 1;
                else if (args[i][j] == 'a')
                    a = 1;
            }
        }

        else
            count++;
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
    //printf("count=%d\n", count);
    if (count == 0)
        show(".", l, a, count);
}
