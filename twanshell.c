#include "headers.h"

int splitter(char *tokens[], char *line, char *delim)
{
  int num = 0; //num stores number of arguments

    tokens[num] = strtok(line, delim);

    while (tokens[num] != NULL)
    {
      tokens[++num] = strtok(NULL, delim);
    }

    tokens[num]=NULL;

    return num;
}

void twanloop()
{

  while (1)
  {

    tildconvertedpwd(tild);

    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);

    char *tokens[100];
    int num = splitter(tokens,line,";");

    for (int now = 0; now < num; now++)
    {

      historyadd(tokens[now]);

      char *args[100];
      int n = splitter(args,tokens[now]," \n\r\t"); //n stores number of arguments

      if (n < 1)
        continue;

      else if (strcmp("pwd", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        pwd(n);
      }

      else if (strcmp("cd", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        cd(args, n);
      }

      else if (strcmp("echo", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        echo(args, n);
      }

      else if (strcmp("ls", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        ls(args, n);
      }

      else if (strcmp("pinfo", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        pinfo(args, n);
      }

      else if (strcmp("history", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        historydisp(args, n);
      }

      else if (strcmp("exit", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        if (n > 1)
          printf("twanshell: exit: Too many arguments\n");
        else
        {
          free(line);
          return;
        }
      }

      else if (strcmp("setenv", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        senv(args, n);
      }

      else if (strcmp("jobs", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        jobs(args, n);
      }

      else if (strcmp("unsetenv", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        unsenv(args, n);
      }

      else if (strcmp("overkill", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        overkill(args, n);
      }

      else if (strcmp("kjob", args[0]) == 0)
      {
        if (strcmp("&", args[n - 1]) == 0)
          n--;
        kjob(args, n);
      }

      else if (strcmp("&", args[n - 1]) == 0)
      {
        n--;
        backgrnd(args,n);
      }

      else
        foregrnd(args);
    }
  }
}

int main(int argc, char **argv)
{
  pidcnt = 0;
  actives = 0; //number of active processes

  getcwd(tild, FILENAME_MAX);
  strcat(tild, &argv[0][1]);
  tild[strlen(tild) - 5] = '\0';

  if (gethostname(hostbuffer, sizeof(hostbuffer)) != 0)
  {
    printf("twanshell: Unable to get hostname\n");
    strcpy(hostbuffer, "HOSTNAME");
  }

  if (getlogin_r(namebuffer, sizeof(namebuffer)) != 0)
  {
    printf("twanshell: Unable to get username\n");
    strcpy(namebuffer, "USERNAME");
  }

  signal(SIGCHLD, child_sig);

  historyinit();

  twanloop();

  historyexit();

  return 0;
}
