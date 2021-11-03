#include <mpi.h>
#include <stdio.h>

#define N 12

int a[N][N],b[N][N],c[N][N];

MPI_Status status;

int main(int argc, char**argv)
{
    MPI_Init(&argc,&argv);
    int id,numprocs;

    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    if(id==0) //master
    {
        printf("Name: Shyam Sundaram\nReg num: 19BCE1560\n\n");
        int co=1;
        for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
        {
            a[i][j]=co++;
            b[i][j]=j+1;
        }

        int rows=N/(numprocs-1),off=0;

        for(int i=1;i<numprocs;++i)
        {
            MPI_Send(&off,1,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Send(&rows,1,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Send(&a[off],rows*N,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Send(&b,N*N,MPI_INT,i,1,MPI_COMM_WORLD);
            off=off+rows;
        }

        for(int i=1;i<numprocs;++i)
        {
            MPI_Recv(&off,1,MPI_INT,i,2,MPI_COMM_WORLD,&status);
            MPI_Recv(&rows, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[off], rows*N, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status);
        }
        printf("Answer is: \n");

        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
                printf("%d ", c[i][j]);
            printf ("\n");
        }
    }

    else //workers
    {
        int off,rows;
        MPI_Recv(&off, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, rows*N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, N*N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        printf("%d rows: %d\n",id,rows);
        /* Matrix multiplication */
        for (int k=0; k<N; k++)
        for (int i=0; i<rows; i++)
        {
            c[i][k] = 0;
            for (int j=0; j<N; j++)
                c[i][k] = c[i][k] + a[i][j] * b[j][k];
        }

        MPI_Send(&off, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}