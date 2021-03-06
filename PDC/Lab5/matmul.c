#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define M 2500
#define N 250
#define L 300

int main()
{
    int chunk = 10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");

    float a[M*L],b[L*N],c[M*N];

    for(int i=0;i<M;++i)
    for(int j=0;j<L;++j)
    a[j+i*L]=10*j+i;

    for(int i=0;i<L;++i)
    for(int j=0;j<N;++j)
    b[j+i*N]=10*j+i;

    for(int i=0;i<M;++i)
    for(int j=0;j<N;++j)
    c[j+i*N]=0;
    
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        float start=omp_get_wtime();
        int chunk=10;
        int i,j,k;
        #pragma omp parallel private(i,j,k) shared(a,b) reduction(+:c)
        {
            #pragma omp for collapse(3)
            for(i=0;i<M;++i)
            {
                for(j=0;j<N;++j)
                {
                    for(k=0;k<L;++k)
                    {
                        c[j+i*N]+=a[k+i*L]*b[j+k*N];
                    }
                }
            }
        }
        
        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f\n",thread[t],exec);
    }
    
    return 0;
}