#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000

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

        float start=omp_get_wtime();
        y[0]=x[0];
        int i,j,sum=0;
        #pragma omp parallel for schedule(guided,chunk) private(i,j,sum)
        for(i=1;i<N;++i)
        {
            sum=0;
            for(j=0;j<=i;++j)
            {
                sum+=x[j];
            }
            y[i]=sum;
        }
        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
        free(y);
    }
    free(x);
}