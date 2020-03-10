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
    esd e[10];
    FILE *inp = fopen("loaderProg.txt","r");
    FILE *esd = fopen("esd.txt","w");
    l[0].rel = 0;
    int extrnLoc;
    int entryLoc;
    int commaCount;
    while(!feof(inp)){
        fscanf(inp,"%s\t%s\t%s",l[i].name,l[i].inst,l[i].arg);
        if(strcmp(l[i].inst,"EXTRN")==0)
            extrnLoc = i;
        if(strcmp(l[i].inst,"ENTRY")==0)
            entryLoc = i;
        if(i>0 && strcmp(l[i-1].inst,"DC")==0){
            int j = 0;
            commaCount = 0;
            int lenArg = strlen(l[i-1].arg);
            while(j<lenArg){
                if((l[i-1].arg)[j] == ',')
                    commaCount += 1;
                j++;
            }
            l[i].rel = l[i-1].rel + 4*(commaCount+1);

        }
        else if(i>0){
            l[i].rel = l[i-1].rel;
        }
        printf("\n%d\t%s\t%s\t%s\n",l[i].rel,l[i].name,l[i].inst,l[i].arg);
        i++;
    }
    int num = i;
    txt t[30];

}
