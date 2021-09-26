#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000

int main()
{
    int chunk=10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};

    long *x=(long*)malloc(N*sizeof(long));
    for(int i=0;i<N;++i)
    {
        x[i]=i;
    }
    
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);

        long *y=(long*)malloc(N*sizeof(long));
        long *z=(long*)malloc(N*sizeof(long));
        #pragma omp parallel for
        for(int i=0;i<N;++i)
        y[i]=x[i];

        float start=omp_get_wtime();
        int d=1;
        while(d<N)
        {
            int i;
            #pragma omp parallel for schedule(guided)
            for(i=d;i<N;++i)
            z[i]=y[i-d];

            #pragma omp parallel for schedule(guided)
            for(i=d;i<N;++i)
            y[i]+=z[i];

            d*=2;
        }
        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
        // for(int i=0;i<N;++i)
        // printf("%ld ",y[i]);
        free(y);
        free(z);
    }
    free(x);
}