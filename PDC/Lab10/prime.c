#include <mpi.h>
#include <stdio.h>

MPI_Status status;

int isPrime(int n)
{
    for(int i=2;i*i<=n;++i)
    {
        if(n%i==0)
        return -1;
    }
    return 1;
}

int main(int argc, char** argv)
{
    MPI_Init(&argc,&argv);

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    if(id==0)   //master
    {
        int s=1,e=1000;
        int num=e-s+1;
        int pernum=num/(numprocs-1);
        int off=s;
        int count=0,ret;
        int leftover=num%(numprocs-1);

        for(int i=1;i<numprocs;++i)
        {
            MPI_Send(&pernum,1,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Send(&off,1,MPI_INT,i,1,MPI_COMM_WORLD);
            off=off+pernum;
        }

        for(int i=1;i<numprocs;++i)
        {
            MPI_Recv(&ret,1,MPI_INT,i,2,MPI_COMM_WORLD,&status);
            count+=ret;
        }

        if(leftover>0)
        {
            for(int i=off;i<off+leftover;++i)
            {
                if(i!=1 && isPrime(i)==1)
                count++;
            }
        }

        printf("Name: Shyam Sundaram\nReg num: 19BCE1560\n\n");
        printf("Total primes: %d\n",count);
    }
    else
    {
        int n,s,count=0;
        MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        MPI_Recv(&s,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        for(int i=s;i<s+n;++i)
        {
            //printf("ID %d: %d %d\n ",id,i,isPrime(i));
            if(i!=1 && isPrime(i)==1)
            count++;
        }
        MPI_Send(&count, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();

}