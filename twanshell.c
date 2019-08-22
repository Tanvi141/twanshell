#include "headers.h"

int main(int argc, char **argv)
{

  char tild[FILENAME_MAX];
  getcwd(tild, FILENAME_MAX);
  strcat(tild,&argv[0][1]);
  tild[strlen(tild)-4]='\0';
  printf("%s\n",tild);

  //if not 0 then error
  char hostbuffer[256];
  gethostname(hostbuffer, sizeof(hostbuffer)); //check for return error
  char namebuffer[256];
  getlogin_r(namebuffer, sizeof(namebuffer));

  int status = 0;

  while (1)
  {

    char converted[FILENAME_MAX];
    tildconvertedpwd(converted, tild);
    printf("<%s@%s:%s> ", namebuffer, hostbuffer, converted);
    char *line = NULL;
    size_t bufsize = 100; //must set appropriate size
    getline(&line, &bufsize, stdin);
    //printf("%s", line);

    char *args[10]; //must set appropriate size
    //how to malloc here?
    //also how to find how many args are there?
    int n = 0; //n stores number of arguments

    args[n] = strtok(line, " \n\r\t");

    while (args[n] != NULL)
    {
      args[++n] = strtok(NULL, " \n\r\t");
    }

   

    if (strcmp("pwd", args[0]) == 0)

      pwd();

    else if (strcmp("cd", args[0]) == 0)
      cd(args, tild, n);

    else if (strcmp("echo", args[0]) == 0)
      echo(args, n);

    else if (strcmp("ls", args[0]) == 0)
      ls(args, n, tild);

    else if (strcmp("pinfo", args[0]) == 0)
      pinfo(args, n);

    else if (strcmp("emacs", args[0]) == 0)
    {
      pid_t pid = fork();

      if (pid == 0)
      {
        //printf("\nChild alice\n");
        execvp(args[0], args);
        
        exit(0);
      }
      else
      {
        //wait(NULL);
        printf("Child ded\n");
      }
    }

    free(line);
    //free(args);
  }
  return 0;
}
