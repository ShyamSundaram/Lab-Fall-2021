#include  <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 8; //must be equal to number of processes
const int m = 5;

void createMatrix(int matrix[n][m], int max_value)
{
    int c=0;   
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d\t",c);
            matrix[i][j] = c++;
        }
        printf("\n");
    }   
}

int main(int argc, char* argv[])
{
    int id = 0;
    int comm_size = 0;

    int mat[n][m]; //the matrix created and distributed by master process
    int row[m]; //one row of matrix to be used by each process
    int colmax[m]; //will contain the maximum of each column
    int colmin[m]; //will contain the minimum of each column

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 

    if (id == 0)
    {
        createMatrix(mat, 10);
        printf("Name: Shyam S\nReg num: 19BCE1560\n\n");
    }
    
    MPI_Scatter(mat, m, MPI_INT, row, m, MPI_INT, 0, MPI_COMM_WORLD);
    
    MPI_Reduce(row, colmax, m, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); //colmax has maximum element of each column
    MPI_Reduce(row, colmin, m, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD); //colmin has minimum element of each column
    // if(id!=0)
    // {
    //     for(int i=0;i<m;++i)
    //     {
    //         printf("process %d element %d = %d\n",id,i,row[i]);
    //     }
    // }
    if (id == 0)
    {
        int max = colmax[0];
        for(int i=1;i<m;++i)
        {
            if(max<colmax[i])
            max=colmax[i];
        }
        int min = colmin[0];
        for(int i=1;i<m;++i)
        {
            if(min>colmin[i])
            min=colmin[i];
        }
        printf("Max: %d\nMin: %d\n",max,min);
    }
    
    MPI_Finalize();

    return 0;
}