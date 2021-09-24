#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

int main()
{
    int chunk =10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");

    int s=N;
    printf("Size of array: %d------------\n",s);

    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        int sum=0;
                
        int i;

        float start=omp_get_wtime();
        #pragma omp parallel for private(i) reduction(+:sum)
        for(i=0;i<N;++i)
            sum+=i;

        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
        
    }
    return 0;
}