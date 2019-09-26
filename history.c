#include "headers.h"

void historyinit()
{
    //initalise all to null?
    char fname[20];
    histptr = 0; //points to next available place
    FILE *fptr = NULL;

    fptr = fopen("hist.txt", "r");
    while (fgets(hists[histptr], 4096, fptr))
    {
        hists[histptr][strlen(hists[histptr]) - 1] = '\0';
        strcat(hists[histptr],"\n");
        histptr++;
        if (histptr > 19)
            break;
    }

    
    histptr %= 20;
    histcnt = histptr;

    fclose(fptr);
 
}

void historyadd(char cmnd[])
{
   
    if (strcmp(hists[(histptr - 1 + 20) % 20], cmnd) == 0)
        return;
    else
    {
        strcpy(hists[histptr], cmnd);
        histptr = (histptr + 1) % 20;
        if (histcnt < 20)
            histcnt++;
    }

    
}

void historydisp(char *args[], int n)
{

    int num;
    if (n == 1)
        num = 10;
    else if (n == 2)
        sscanf(args[1], "%d", &num);
    else
        fprintf(stderr,"twanshell: history: Too many arguments\n");

    if (num > 10)
        num = 10;
    if (num > histcnt)
        num = histcnt;


    for (int i = num; i > 0; i--)
    {
        printf("%s\n", hists[(histptr - i + 20) % 20]);
    }
}

void historyexit()
{

    FILE *fp;
    fp = fopen("hist.txt", "w");

    for (int i = histcnt; i > 0; i--)
    {
        fputs(hists[(histptr - i + 20) % 20],fp);
    }

    fclose(fp);
    return;
}