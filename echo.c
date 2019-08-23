#include "headers.h"

void echo(char *args[], int n)
{

  if (n < 2) //no arguments
  {
    return;
  }
  else if (args[1][0] == '\"' && args[n - 1][strlen(args[n - 1]) - 1] == '\"')  //in double quotes
  {
    args[1]++;
    args[n - 1][strlen(args[n - 1]) - 1] = '\0';
  }

  else if (args[1][0] == '\'' && args[n - 1][strlen(args[n - 1]) - 1] == '\'')  //in single quotes
  {
    args[1]++;
    args[n - 1][strlen(args[n - 1]) - 1] = '\0';
  }

  for (int i = 1; i < n - 1; i++)
  {
    if (args[i] != NULL)
      printf("%s ", args[i]);
  }
  if (args[n - 1] != NULL)
    printf("%s", args[n - 1]);
}