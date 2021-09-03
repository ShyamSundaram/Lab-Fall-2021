#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define R 2500
#define C 250

int main()
{
    int chunk = 10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");

    float a[R][C], b[C][C], c[R][C];

    for(int i=0;i<R;++i)
    for(int j=0;j<C;++j)
    a[i][j]=10*j+i;

    for(int i=0;i<C;++i)
    for(int j=0;j<C;++j)
    b[i][j]=10*i+j;

    for(int i=0;i<R;++i)
    for(int j=0;j<C;++j)
    c[i][j]=0;

    
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        float start=omp_get_wtime();
        int chunk=10;
        int i,j,k;
        #pragma omp parallel private(i,j,k) shared(a,b) reduction(+:c)
        {
            #pragma omp for collapse(3)
            for(i=0;i<R;++i)
                for(j=0;j<C;++j)
                    for(k=0;k<C;++k)
                        c[i][j]+=a[i][k]*b[k][j];
            
        }
        
        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
    }
    
    return 0;
}