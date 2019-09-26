#include "headers.h"

void pwd(int n)
{
  if (n > 1)
  {
    fprintf(stderr,"twanshell: pwd: too many arguments\n");
    return;
  }
  char buffer[FILENAME_MAX];
  getcwd(buffer, FILENAME_MAX);
  printf("%s\n", buffer);
}

void tildconvertedpwd()
{
  //this function is used to print the command prompt
  char converted[FILENAME_MAX];
  char current[FILENAME_MAX];
  getcwd(current, FILENAME_MAX);
  tildconverter(converted, current);
  printf("<%s%s@%s%s:%s%s%s> ", "\x1B[1;34m", namebuffer, hostbuffer, "\x1B[0m", "\x1B[1;32m", converted, "\x1B[0m");
}

void tildconverter(char converted[], char current[])
{
  int flag = 0;
  if (strlen(current) >= strlen(tild))
  {
    for (int i = 0; i < strlen(tild); i++)
    {
      if (current[i] != tild[i])
      {
        flag = 1;
        break;
      }
    }
  }
  else
    flag = 1; //means we can replace a tilda

  strcpy(converted, "~");
  if (flag == 0)
  {
    strcat(converted, &current[strlen(tild)]);
  }

  else
  {
    strcpy(converted, current);
  }
}