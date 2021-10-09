#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000

void bubbleSort(int a[])
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

void main()
{
    bubblesort();
}