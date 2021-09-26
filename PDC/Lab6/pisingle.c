#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define terms 10000000

int main()
{
    
    int chunk = 10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        int i=3;
        double *sum=malloc(sizeof(double)*thread[t]);
        for(int k=0;k<thread[t];++k)
        sum[k]=0;
        double pi=4;
        double ps;
        float start=omp_get_wtime();
        #pragma omp parallel private(i,ps) shared(sum)
        {

            #pragma omp for schedule(guided,chunk) 
            for(i=3;i<2*terms;i+=2)
            {
                ps=((pow(-1,i/2)*4)/i);
                sum[omp_get_thread_num()]+=ps;
            }

            #pragma omp single
            {
                for(int k=0;k<thread[t];++k)
                pi+=sum[k];
            }
        }
        printf("sum= %f ",pi);
        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
        free(sum);
    }
    return 0;
}