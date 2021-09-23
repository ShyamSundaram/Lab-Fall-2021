#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define N 60000
int main()
{
    omp_set_num_threads(5);
    #pragma omp parallel
    {
        printf("out %d\n",omp_get_thread_num());
        #pragma omp for
        for(int i=0;i<10;++i)
        printf("%d\n",omp_get_thread_num());
    }
    
    return 0;
}