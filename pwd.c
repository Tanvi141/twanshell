#include "headers.h"

void pwd()
{
  char buffer[FILENAME_MAX];
  getcwd(buffer, FILENAME_MAX);
  printf("%s\n", buffer); //what if pipe
}

void tildconvertedpwd(char converted[], char tild[])
{
  char current[FILENAME_MAX];
  getcwd(current, FILENAME_MAX);
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
    flag = 1;

  strcpy(converted,"~");
  if (flag == 0)
  {
    strcat(converted, &current[strlen(tild)]); // assuming not .. from tild
  }

  else
  {
    strcpy(converted, current);
  }
}

// void convertreltoabs(char converted[], char tild[])