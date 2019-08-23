#include "headers.h"

void twanloop()
{

  while (1)
  {

    tildconvertedpwd(tild);

    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);

    char *tokens[100];
    int num = 0; //n stores number of arguments

    tokens[num] = strtok(line, ";");

    while (tokens[num] != NULL)
    {
      tokens[++num] = strtok(NULL, ";");
    }

    for (int now = 0; now < num; now++)
    {

      char *args[100];
      int n = 0; //n stores number of arguments

      args[n] = strtok(tokens[now], " \n\r\t");

      while (args[n] != NULL)
      {
        args[++n] = strtok(NULL, " \n\r\t");
      }

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

      else if (strcmp("&", args[n - 1]) == 0)
      {
        backgrnd(args);
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

  twanloop();

  return 0;
}
