#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int sieve(int x)
{
    for(int i=2;i*i<=x;++i)
    {
        if(x%i==0)
        return -1;
    }
    return 1;
}

int main()
{
    int N[]={1000,10000,100000,1000000};
    int chunk = 10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab:\n\n");


    for(int i=0;i<4;++i)
    {
        printf("-------\nN: %d\n",N[i]);
        for(int t=0;t<10;++t)
        {
            omp_set_num_threads(thread[t]);
            float start=omp_get_wtime();
            int cnt=0;
            int n=N[i];
            #pragma omp parallel for schedule(dynamic,chunk) reduction(+:cnt) //for static, replace dynamic with static and for default, remove the schedule clause itself
            for(int j=2;j<n;++j)
            {
                if(sieve(j)==1)
                cnt+=1;
            }
            
            float end=omp_get_wtime();
            float exec=end-start;
            printf("Count: %d Thread count: %d Time taken is: %f\n",cnt,thread[t],exec);
        }
    }
    return 0;
}