#include "headers.h"

void echo(char *args[], int n)
{
  args[1]++; //is its size>0 now?
  args[n - 1] = strtok(args[n - 1], "\"");
  for (int i = 1; i < n - 1; i++)
  {
    if (args[i] != NULL)
      printf("%s ", args[i]);
  }
  if (args[n - 1] != NULL)
    printf("%s", args[n - 1]);
}