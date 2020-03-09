#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct load{
    int rel;
    char name[30];
    char inst[30];
    char arg[30];
}loader;

typedef struct esdTab{
    char name[30];
    char type[30];
    char id[30];
    int rel;
    int length;
} esd;

typedef struct txtTab{
    int rel;
    int content;
} txt;

int main()
{
    int n=30 , i = 0;
    loader l[n];
    esd e[n];
    txt t[n];
    rld r[n];	
    FILE *inp = fopen("loaderProg.txt","r");
    FILE *esd = fopen("esd.txt","w");    
}
