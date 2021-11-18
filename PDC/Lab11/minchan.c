
#include<mpi.h>
#include<stdio.h>
#include<limits.h>
#define M 10
#define N 10

int main(int argc,char**argv)
{
    int A[M][N],min=INT_MAX,max=INT_MIN,min1=INT_MAX,max1=INT_MIN,a=INT_MAX,b=INT_MIN;
    MPI_Init(&argc,&argv);
    float startwtime,endwtime,totalTime;
    int myid;


    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    int numprocs;
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    int s=M/numprocs;
    int s0=M%numprocs;
    if(myid==0)
    {
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<N;j++)
            {
                A[i][j]=M*N-(i*N+j);
                printf("%d ",A[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    int *B=(int *)malloc(s*N*sizeof(int));
    MPI_Scatter(&A[s0],s*N,MPI_INT,B,s*N,MPI_INT,0,MPI_COMM_WORLD);
    totalTime=0;
    if(myid==0)
    {
        startwtime=MPI_Wtime();
        for(int i=0;i<s0;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(A[i][j]<min1)
                {
                    min1=A[i][j];
                }
                if(A[i][j]>max1)
                {
                    max1=A[i][j];
                }
            }
        }
    }
    for(int i=0;i<s*N;i++)
    {
        if(B[i]<min)
            min=B[i];
        if(B[i]>max)
            max=B[i];
    }
    if(s0<M)
    {
        MPI_Reduce(&min,&a,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
        MPI_Reduce(&max,&b,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
    }
    if(myid==0)
    {
        printf("%d %d %d %d\n",a,b,min1,max1);
        printf("Minimum ele:%d\n",a<min1?a:min1);
        printf("Maximum ele:%d\n",b>max1?b:max1);
        endwtime=MPI_Wtime();
        totalTime=endwtime-startwtime;
        printf("Execution time %f sec\n",totalTime);
    }
    MPI_Finalize();
}