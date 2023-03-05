
#include <fmt/core.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  fmt::print("Hello world! Rank: {} of {}\n", rank, size);
  MPI_Finalize();
}