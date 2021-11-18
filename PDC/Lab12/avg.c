#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 225; //height of image
const int m = 225; //width of image

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

int main(int argc, char* argv[])
{
    int r[n][m],g[n][m],b[n][m];
    
    int id = 0;
    int comm_size = 0;
    
    int final[n][m];

    int start,siz;
    readMatrix(r,0);
    readMatrix(g,1);
    readMatrix(b,2);
    
    double t1, t2; 
    t1 = MPI_Wtime(); 
 

     

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    start=n%comm_size;
    siz=n/comm_size;
    if(id==0)
    {
        readMatrix(r,0);
        readMatrix(g,1);
        readMatrix(b,2);
        
        printf("Name: S Shyam Sundaram\nReg num: 19BCE1560\n\n");
        printf("%d and %d\n",start,siz);
        if(start!=0)
        {
            for(int i=0;i<start;++i)
            for(int j=0;j<m;++j)
            final[i][j]=(r[i][j]+g[i][j]+b[i][j])/3;
        }
    }
    int rrow[m*siz],grow[m*siz],brow[m*siz], avg[m*siz];
    MPI_Scatter(r[start], siz*m, MPI_INT, rrow, siz*m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(g[start], siz*m, MPI_INT, grow, siz*m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b[start], siz*m, MPI_INT, brow, siz*m, MPI_INT, 0, MPI_COMM_WORLD);

    
    for(int k=0;k<m*siz;++k)
        avg[k]=(rrow[k]+grow[k]+brow[k])/3;
    
    if(start<m)
    MPI_Gather(avg,siz*m,MPI_INT,final[start],siz*m,MPI_INT,0,MPI_COMM_WORLD);

    if(id==0)
    {
        printf("Final is matrix written to file \n");
        writeMatrix(final);
    }

    MPI_Finalize();
    t2 = MPI_Wtime(); 
    printf( "Elapsed time is %f\n", t2 - t1 ); 
    return 0;
}