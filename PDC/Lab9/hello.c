#include<mpi.h>
#include<stdio.h>

int main(int argc, char**argv)
{

MPI_Init(NULL,NULL);

int myid;
MPI_Comm_rank(MPI_COMM_WORLD, &myid);

int numprocs;
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

int namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Get_processor_name(processor_name, &namelen);

printf("Helloworld from processor %s, rank %d out of %d processors\n", processor_name,myid,numprocs);

MPI_Finalize();
}
