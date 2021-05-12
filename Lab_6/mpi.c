#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 

int main(int argc, char **argv) 
{ 
    int rank, num_proc, i;
    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
    MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
    MPI_Status status;

    double start = MPI_Wtime();
    int n = 100000;
    if(rank == 0) 
    { 
        for (i = 1; i < num_proc; i++)
        {
            MPI_Send(&rank, n, MPI_BYTE, i, 1, MPI_COMM_WORLD);
        }
    } 
    else 
    { 
        MPI_Recv(&rank, n, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &status); 
        double end = MPI_Wtime();
        double time = end - start;
        printf("The process took %lf seconds\n", time);
    }
    MPI_Finalize(); 
    return(0); 
}
