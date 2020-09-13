
#include <mpi.h>
#include <cstdio>

int  main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello world! Rank: %d of %d \n", rank, size);
    MPI_Finalize();
}