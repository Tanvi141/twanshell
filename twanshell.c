#include "headers.h"

void twanloop()
{

  //freee
  while (1)
  {
    
    tildconvertedpwd(tild);
    
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    
    char *tokens[100]; //must set appropriate size
    //how to malloc here?
    //also how to find how many tokens are there?
    int num = 0; //n stores number of arguments

    tokens[num] = strtok(line, ";");

    while (tokens[num] != NULL)
    {
      tokens[++num] = strtok(NULL, ";");
    }
    
    for (int now = 0; now < num; now++)
    {

      char *args[100]; //must set appropriate size
      //how to malloc here?
      //also how to find how many args are there?
      int n = 0; //n stores number of arguments

      args[n] = strtok(tokens[now], " \n\r\t");
      
      while (args[n] != NULL)
      {
        args[++n] = strtok(NULL, " \n\r\t");
      }
      
      if(n<1) continue;
      else if(strcmp("&", args[n-1]) == 0)
        backgrnd(args);
     
      else if (strcmp("pwd", args[0]) == 0)
        pwd();

      else if (strcmp("cd", args[0]) == 0)
        cd(args, tild, n);

      else if (strcmp("echo", args[0]) == 0)
        echo(args, n);

      else if (strcmp("ls", args[0]) == 0)
        ls(args, n, tild);

      else if (strcmp("pinfo", args[0]) == 0)
        pinfo(args, n);

      else if (strcmp("exit", args[0]) == 0)
        return;

      else foregrnd(args);


    }
  }
}

int main(int argc, char **argv)
{
  pidcnt=0;
  getcwd(tild, FILENAME_MAX);
  strcat(tild, &argv[0][1]);
  tild[strlen(tild) - 5] = '\0';

  //if not 0 then error

  gethostname(hostbuffer, sizeof(hostbuffer)); //check for return error

  getlogin_r(namebuffer, sizeof(namebuffer));
  signal(SIGCHLD, child_sig);

  twanloop();

  return 0;
}
