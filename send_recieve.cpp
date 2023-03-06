#include <fmt/core.h>
#include <mpi.h>

#include <numeric>
#include <vector>

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int my_value;

  if (rank == 0) {
    std::vector<int> values(size, -1);
    std::iota(begin(values), end(values), 1);

    my_value = values[0];
    for (int i = 1; i < size; ++i) {
      MPI_Send(&values[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  } else {
    MPI_Status status;
    MPI_Recv(&my_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  fmt::print("Value = {}: Rank = {}/{}\n", my_value, rank, size);
  MPI_Finalize();
}