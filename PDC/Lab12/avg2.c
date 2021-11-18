#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 479; //height of image
const int m = 500; //width of image

void readMatrix(int matrix[n][m],int color)
{
    FILE *fp;
    if(color==0) //0: red, 1: green, anything else: blue
    fp = fopen("r.txt", "r");
    else if(color==1)
    fp = fopen("g.txt", "r");
    else
    fp = fopen("b.txt", "r");

    int r=0,c=0;
    int x;

    while((fscanf(fp,"%d,",&x)!=EOF))
    {
        //printf("%d-",x);
        if(c==m)
        {
            r++;
            c=0;
        }
        matrix[r][c++]=x;
    }

    fclose(fp);
}

void writeMatrix(int matrix[n][m])
{
    FILE *fp;
    fp=fopen("final.txt","a");
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            fprintf(fp,"%d, ",matrix[i][j]);
        }
        fprintf(fp,"\n");
    }

    fclose(fp);
}

void createMatrix(int matrix[n][m], int max_value)
{
    
    int t;
    for (int i = 0; i < n; i++)
    {
        
        for (int j = 0; j < m; j++)
        {
            t=rand()%max_value;
            printf("%d\t",t);
            matrix[i][j] = t;
        }
        printf("\n");
    }   
}

int main(int argc, char* argv[])
{
    int r[n][m],g[n][m],b[n][m];
    int rrow[m],grow[m],brow[m];
    int id = 0;
    int comm_size = 0;
    int avg[m];
    int final[n][m];

    int start,siz;
    readMatrix(r,0);
    readMatrix(g,1);
    readMatrix(b,2);
    

    //readMatrix(r);
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    if(id==0)
    {
        // printf("R is: \n");
        // createMatrix(r,10);
        // printf("G is: \n");
        // createMatrix(g,10);
        // printf("B is: \n");
        // createMatrix(b,10);
        readMatrix(r,0);
        readMatrix(g,1);
        readMatrix(b,2);
        start=n%comm_size;
        siz=n/comm_size;
        if(start!=0)
        {
            for(int i=0;i<start;++i)
            for(int j=0;j<m;++j)
            final[i][j]=(r[i][j]+g[i][j]+b[i][j])/3;
        }
    }

    MPI_Scatter(r[start], m, MPI_INT, rrow, m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(g[start], m, MPI_INT, grow, m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b[start], m, MPI_INT, brow, m, MPI_INT, 0, MPI_COMM_WORLD);

    // for(int j=0;j<3;++j)
    // {
    //     if(id==j)
    //     {
    //         for(int i=0;i<m;++i)
    //         printf("from id %d i %d and rrow: %d\n",id,i,rrow[i]);

    //         for(int i=0;i<m;++i)
    //         printf("from id %d i %d and grow: %d\n",id,i,grow[i]);

    //         for(int i=0;i<m;++i)
    //         printf("from id %d i %d and brow: %d\n",id,i,brow[i]);

    //         // for(int k=0;k<m;++k)
    //         // avg[k]=(rrow[k]+grow[k]+brow[k])/3;
    //     }
    // }
    
    for(int k=0;k<m;++k)
        avg[k]=(rrow[k]+grow[k]+brow[k])/3;
    
    MPI_Gather(avg,m,MPI_INT,final[start],m,MPI_INT,0,MPI_COMM_WORLD);

    if(id==0)
    {
        printf("Final is: \n");
        // for(int i=0;i<n;++i)
        // {
        //     for(int j=0;j<m;++j)
        //     printf("%d\t",final[i][j]);
        //     printf("\n");
        // }

        writeMatrix(final);
    }

    // for(int i=0;i<m;++i)
    // printf("from id %d i %d and rrow: %d\n",id,i,rrow[i]);

    // for(int i=0;i<m;++i)
    // printf("from id %d i %d and grow: %d\n",id,i,grow[i]);

    // for(int i=0;i<m;++i)
    // printf("from id %d i %d and brow: %d\n",id,i,brow[i]);

    MPI_Finalize();
}