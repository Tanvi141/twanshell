#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <poll.h>
#include <syslog.h>

char hostbuffer[256];
char namebuffer[256];
char tild[FILENAME_MAX];
int pids[100];
int pidcnt;

void pwd();
void cd(char *args[], char tild[],int n);
void echo(char *args[], int n);
void tildconvertedpwd(char tild[]);
void ls(char *args[], int n, char tild[]);
void pinfo(char *args[], int n);
void child_sig();
void foregrnd(char *args[]);
void backgrnd(char *args[]);