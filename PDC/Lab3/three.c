#include <stdio.h>
#include "omp.h"
#include<time.h>

#define N 600000

int main()
{
    float a[N],b[N],c[N];
    int i;
    int m=650000;
    //clock_t t;
    float start,end,exec;
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");

    for(i=0;i<N;++i)
    {
        
        a[i]=(i+1)*1.0;
        b[i]=(i+1)*2.0;
    }
    //t=clock();
    //start=omp_get_wtime();

    int thread[]={1,2,4,8,16,32,64,128,256,512};
    float serial;
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        start=omp_get_wtime();
        #pragma omp parallel default(none), private(i,m), shared(a,b,c)
        {
            #pragma omp for
            for(i=0;i<N;++i)
            {
                for(int j=0;j<1000;++j)
                c[i]=a[i]+b[i];
            }
        }
        //t=clock()-t;
        //double exec=((double)t)/CLOCKS_PER_SEC;
        end=omp_get_wtime();
        exec=end-start;
        if(t==0) serial=exec;
        printf("Thread count: %d Time taken is: %f  ",thread[t],exec);
        float pf=(1-(exec/serial))/(1-(1/thread[t]));
        printf(" PF = %f ",pf);
        float s=1-pf;
        float speedup=1/(s+(pf/thread[t]));
        printf(" Speedup = %f\n",speedup);
    }
    return 0;
}