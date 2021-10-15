#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int main()
{
    FILE *fptr;
    int num;
    fptr=fopen("num.txt","w");
    srand(time(0));
    int upper=1000,lower=10;
    for(int i=0;i<N;++i)
    {
        num=i+1;//(rand()%(upper-lower+1))+lower;
        putw(num,fptr);
    }
    fclose(fptr);

    fptr=fopen("num.txt","r");

    while((num=getw(fptr))!=EOF)
    {
        printf("%d\n",num);
    }
    fclose(fptr);
    return 0;

}