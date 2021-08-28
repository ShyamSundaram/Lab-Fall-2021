#include <stdio.h>
#include "omp.h"
#include<time.h>

#define ROWS 2500
#define COLS 250

int main()
{
    float a[ROWS][COLS],b[ROWS][COLS],c[ROWS][COLS];
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");

    for(int i=0;i<ROWS;++i)
    for(int j=0;j<COLS;++j)
    {
        a[i][j]=i*10+j;
        b[i][j]=j*10+i;
    }
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    float serial;
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        float start=omp_get_wtime();

        #pragma omp parallel for shared(a,b,c) //reduction(+: c)
        for(int i=0;i<ROWS;++i)
        for(int j=0;j<COLS;++j)
        {
            for(int j=0;j<1000;++j)
            c[i][j]=a[i][j]+b[i][j];
        }
        float end=omp_get_wtime();
        float exec=end-start;
        if(t==0) serial=exec;

        printf("Thread count: %d Time taken is: %f",thread[t],exec);
        float pf=(1-(exec/serial))/(1-(1/thread[t]));
        printf(" PF = %f ",pf);
        float s=1-pf;
        float speedup=1/(s+(pf/thread[t]));
        printf(" Speedup = %f\n",speedup);
    }
    return 0;

}