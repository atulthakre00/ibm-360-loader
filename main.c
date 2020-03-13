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

int entryRelLocn(char entry[] , loader l[] ,int n){
    for(int i=0;i<n;i++){
        if(strcmp(l[i].name , entry) == 0)
            return(l[i].rel);
    }
}

int relLocnESD(char a[] , esd e[] ,int n){
    for(int i=0;i<n;i++){
        if(strcmp(e[i].name , a) == 0)
            return(e[i].rel);
    }
}

int esdMaker(esd e[],loader l[],int num){
    strcpy(e[0].name,l[0].name);
    strcpy(e[0].type,"SD");
    strcpy(e[0].id,"01");
    e[0].rel = 0;
    e[0].length = l[num-1].rel;

    int argLen = strlen(l[1].arg) , i = 0 ,esdPointer = 1;
    while(i<argLen){
        int j = 0;
        char temp[30];
        while(i<argLen && l[1].arg[i] != ',' && l[1].arg[i] != ' '){
            temp[j] = l[1].arg[i];
            i++;
            j++;
        }
        temp[j] = '\0';
        strcpy(e[esdPointer].name,temp);
        strcpy(e[esdPointer].type,"LD");
        strcpy(e[esdPointer].id,"--");
        e[esdPointer].length = 0;
        e[esdPointer].rel = entryRelLocn(e[esdPointer].name , l , num);
        esdPointer++;
        i++;
    }
    argLen = strlen(l[2].arg);
    i = 0;
    int erCount = esdPointer - 2;
    while(i<argLen){
        int j = 0;
        char temp[30];
        while(i<argLen && l[2].arg[i] != ',' && l[2].arg[i] != ' '){
            temp[j] = l[2].arg[i];
            i++;
            j++;
        }
        temp[j] = '\0';
        char tt[30];
        sprintf(tt,"0%d",(esdPointer - erCount));
        strcpy(e[esdPointer].name,temp);
        strcpy(e[esdPointer].type,"ER");
        strcpy(e[esdPointer].id,tt);
        e[esdPointer].length = 0;
        e[esdPointer].rel = 0;
        esdPointer++;
        i++;
    }

    return(esdPointer);
}

void printESD(esd e[],int esdPointer){
    printf("\nESD Table\n");
    printf("\n%s\t%s\t%s\t%s\t%s\n","Name","Type","ID","Rel","Length");
    for(int i=0;i<esdPointer;i++)
        printf("\n%s\t%s\t%s\t%d\t%d\n",e[i].name,e[i].type,e[i].id,e[i].rel,e[i].length);

}

addressConstEvaluator(char address[] ,esd e[] , int esdPointer){
    int len = strlen(address);
    int i = 2;
    int ans = 0;
    char op = '+';
    while(i<len){
        int pointer = 0;
        char temp[30];
        while(i<len && address[i] != ')'){
            if(address[i] == '+' || address[i] == '-'){
                break;
            }
            else
                temp[pointer++] = address[i++];
        }
        temp[pointer] = '\0';
        if(op == '+'){
            if(temp[0] > '0' && temp[0] < '9')
                ans += atoi(temp);
            else
                ans += relLocnESD(temp , e ,esdPointer);
        }
        else{
             if(temp[0] > '0' && temp[0] < '9')
                ans -= atoi(temp);
            else
                ans -= relLocnESD(temp , e ,esdPointer);
        }
        op = address[i];
        printf("\n#%s %d#\n",temp,ans);
        i++;
    }
    return(ans);
}

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
    int esdPointer = esdMaker(e,l,num);
    printESD(e,esdPointer);

    return 0;
}
