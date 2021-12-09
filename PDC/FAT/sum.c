#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>

#define X 100
#define Y 1000
#define Z 1000

int main()
{
    int chunk = 10;
    int thread[]={1,2,4,8,16,32,64,128,256,512};
    
    printf("Name: Shyam Sundaram\nReg num: 19BCE1560\nPDC Lab FAT:\n\n");

    int x[X],y[Y],z[Z];

    srand(time(0));

    for(int l=0;l<X;++l)
    x[l]=(rand()%(100-1+1))+1;

    for(int l=0;l<Y;++l)
    y[l]=(rand()%(100-1+1))+1;

    for(int l=0;l<Z;++l)
    z[l]=(rand()%(100-1+1))+1;


    // int x[]={10,20,20,20};
    // int y[]={10,20,30,40};
    // int z[]={10,30,40,20};

    int target=70;
    
    for(int t=0;t<10;++t)
    {
        omp_set_num_threads(thread[t]);
        float start=omp_get_wtime();
        int chunk=10;
        int i,j,k,c=0;
        #pragma omp parallel private(i,j,k) shared(x,y,z) reduction(+:c)
        {
            #pragma omp for schedule(guided,10) collapse(3)
            for(i=0;i<X;++i)
                for(j=0;j<Y;++j)
                    for(k=0;k<Z;++k)
                    {
                        if(x[i]+y[j]+z[k]==target)
                        {
                            c+=1;
                        }
                    }
        }
        
        float end=omp_get_wtime();
        float exec=end-start;
        printf("Thread count: %d Time taken is: %f Number of combinations: %d\n",thread[t],exec,c);
    }


    return 0;
}