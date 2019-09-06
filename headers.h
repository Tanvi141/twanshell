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

struct procs{
    pid_t pid;
    char name[100];
    int status;  // 1 means running, 0 means not
};
struct procs pids[1024];
int pidcnt;
int actives;

char hists[20][4096];
int histptr;
int histcnt;

extern int alphasort();
void pwd(int n);
void cd(char *args[],int n);
void echo(char *args[], int n);
void tildconvertedpwd();
void ls(char *args[], int n);
void pinfo(char *args[], int n);
void child_sig();
void foregrnd(char *args[]);
void backgrnd(char *args[],int n);
void tildconverter(char converted[],char current[]);
void historyinit();
void historyadd(char cmnd[]);
void historydisp(char *args[], int n);
void historyexit();
void senv(char *args[], int n);
void unsenv(char *args[], int n);
void jobs(char *args[],int n);
void overkill(char *args[], int n);
void kjob(char *args[], int n);