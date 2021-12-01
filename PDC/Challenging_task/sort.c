#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n=10000;

void swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}

void fillArray(int a[],int x)
{
    srand(time(0));

    for(int i=0;i<x;++i)
    {
        a[i]=(rand()%(100-1+1))+1;
    }
}

void merge(int a[],int m,int r)
{
    int x[r],c=0;

    int i=0,j=m;

    while(i<m && j<r)
    {
        if(a[i]<a[j])
        x[c++]=a[i++];
        else
        x[c++]=a[j++];
    }

    while(i<m)
    x[c++]=a[i++];

    while(j<r)
    x[c++]=a[j++];

    for(int k=0;k<r;++k)
    a[k]=x[k];
}

int main(int argc,char* argv[])
{
    int a[n];

    fillArray(a,n);
    
    int id=0,start,siz;
    int comm_size=0;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    double t1, t2; 
    
    start=n%comm_size;
    siz=n/comm_size;

    if(id==0)
    {
        printf("Name: S Shyam Sundaram\nReg num: 19BCE1560\n\n");
        t1 = MPI_Wtime();
        if(start!=0)
        {
            int temp;
            for(int i=0;i<start-1;++i)
            {
                for(int j=0;j<start-i-1;++j)
                {
                    if(a[j]>a[j+1])
                    {
                        swap(&a[j],&a[j+1]);
                    }
                }
            }
        }
    }
    int arr[siz];
    MPI_Scatter(&a[start],siz,MPI_INT,arr,siz,MPI_INT,0,MPI_COMM_WORLD);

    for(int i=0;i<siz-1;++i)
    for(int j=0;j<siz-i-1;++j)
    {
        if(arr[j]>arr[j+1])
        {
            swap(&arr[j],&arr[j+1]);
        }
    }

    MPI_Gather(arr,siz,MPI_INT,&a[start],siz,MPI_INT,0,MPI_COMM_WORLD);

    if(id==0)
    {
        // for(int i=0;i<n;++i)
        // printf("%d ",a[i]);
        // printf("\n");
        int off=siz;
        if(start!=0)
        {
            off=start+siz;
            //merge(a,start,start+siz);
        }
        while(off<n)
        {
            // printf("off is %d and off+siz is %d\n",off,off+siz);
            merge(a,off,off+siz);
            off=off+siz;
        }
        // for(int i=0;i<n;++i)
        // printf("%d ",a[i]);
        // printf("\n");
        t2 = MPI_Wtime(); 
        printf( "Elapsed time is %f\n", t2 - t1 ); 
    }

    MPI_Finalize();
    return 0;
   
}