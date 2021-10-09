#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 10000

int* initArray(int r,int u,int l)
{
    srand(time(0));

    int *arr=(int*)malloc(r*sizeof(int));
    
    for(int j=0;j<r;++j)
        arr[j]=(rand()%(u-l+1))+l;

    
    return arr;
}

void freeArray(int* arr)
{
    free(arr);
}

void bubbleSortSerial(int a[])
{
    int temp;
    for(int i=0;i<SIZE;++i)
    {
        for(int j=i;j<SIZE;++j)
        {
            if(a[i]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void bubbleSortParallel(int a[])
{
    omp_set_num_threads(4);
    for(int i=0;i<SIZE;++i)
    {
        int first=i%2;
        #pragma omp paralel for default(none) shared(a,first)
        for(int j=first;j<SIZE-1;j+=2)
        {
            if(a[j]>a[j+1])
            {
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void main()
{
    int *a=initArray(SIZE,100,0);
    int *b=initArray(SIZE,100,0);

    float start=omp_get_wtime();
    bubbleSortSerial(a);
    float end=omp_get_wtime();
    float exec=end-start;
    printf("Time taken is: %f\n",exec);
    freeArray(a);

    start=omp_get_wtime();
    bubbleSortParallel(b);
    end=omp_get_wtime();
    exec=end-start;
    printf("Time taken is: %f\n",exec);
    
    freeArray(b);
}

//https://gcc.gnu.org/onlinedocs/gcc/Invoking-Gcov.html#Invoking-Gcov