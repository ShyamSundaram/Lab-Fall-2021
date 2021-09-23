#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define terms 100

int main()
{
    double sum=4;
    double ps;
    for(int i=3;i<2*terms;i+=2)
    {
        ps=((pow(-1,i/2)*4)/i);
        printf("%f\n",ps);
        sum=sum+ps;
    }
    printf("sum= %f",sum);
    return 0;
}