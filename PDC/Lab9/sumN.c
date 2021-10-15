#include <mpi.h>
#include<stdio.h>
#define MAXSIZE 100
int main(int argc, char**argv)
{

    MPI_Init(&argc,&argv);
    float startwtime,endwtime,totalTime;
    int myid;
    long int s,s0,startIndex,endIndex;
    long int i;
    float sum,part_sum;
    float data[MAXSIZE];
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    int numprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(processor_name, &namelen);
    FILE *fp;

    fprintf(stderr,"Process %d is on %s\n",myid,processor_name);
    fflush(stderr);

    for(i=0;i<MAXSIZE;i++)
    {
        data[i]=i+1;
    }
    if(myid==0)
    {//master
        s=(int)(MAXSIZE/numprocs);
        s0=s+(MAXSIZE%numprocs);
        printf("s=%ld,s0=%ld \n",s,s0);
    }
    else
    {
        //worker
        s=(int)(MAXSIZE/numprocs);
        s0=s+(MAXSIZE%numprocs);
        startIndex = s0+(myid-1)*s;
        endIndex=startIndex+s;
        }
    //Broadcasting
    MPI_Bcast(&s,1,MPI_FLOAT,0,MPI_COMM_WORLD);
    MPI_Bcast(&s0,1,MPI_FLOAT,0,MPI_COMM_WORLD);

    //Time
    totalTime=0;
    if(myid==0)
    {
        startwtime=MPI_Wtime();
    }
    //Partial Sum
    if(myid==0)
    {
        //master partial sum
        for(i=0;i<s0;i++)
        {
            part_sum = part_sum+data[i];
        }
        printf("Partial Sum from master = %f from processor %d\n", part_sum,myid);
    }
    else
    {
        //worker partial sum
        for(i=startIndex;i<endIndex;i++)
        {
            part_sum=part_sum+data[i];
        }
        printf("Partial Sum from worker = %f from processor %d\n", part_sum,myid);
    }

    //Global Sum
    MPI_Reduce(&part_sum,&sum,1, MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

    if(myid==0)
    {
        endwtime=MPI_Wtime();
        totalTime=endwtime-startwtime;
        printf("Global Sum is %f\n", sum);
        printf("Execution time %f sec\n",totalTime);
    }

    MPI_Finalize();
}
