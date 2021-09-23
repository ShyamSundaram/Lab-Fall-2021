#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define N 100000000
int main()
{
    int chunk =20;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");

    // int a[N];
    
    // for(int i=0;i<N;++i)
    // a[i]=1;

    int s=N;
    printf("Size of array: %d------------\n",s);
    
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        long *sum=(long*)malloc(thread[t]*sizeof(long));
        for(int i=0;i<thread[t];++i)
        sum[i]=0;
        long s=0;
        int i;
        float start=omp_get_wtime();
        #pragma omp parallel for schedule(static,chunk) shared(sum) private(i)
        for(i=0;i<N;++i)
        sum[omp_get_thread_num()]+=i;
        
        for(int i=0;i<thread[t];++i)
        s+=sum[i];
        float end=omp_get_wtime();
        float exec=end-start;
        //printf("%ld\n",s);
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
        free(sum);
    }
    return 0;
}