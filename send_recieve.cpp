#include <mpi.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

enum ErrorCode {
  FileNotFound,
};

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int my_value;

  if (rank == 0) {
    std::ifstream file("test.dat");

    std::cout << "Opening test.dat\n";

    if (!file.is_open()) {
      std::cerr << "File 'test.dat' is not found!\n";
      MPI_Abort(MPI_COMM_WORLD, ErrorCode::FileNotFound);
    }

    std::cout << "Reading test.dat\n";

    std::vector<int> values(size, -1);
    for (int i = 0; i < size; ++i) {
      file >> values[i];
      if (file.eof()) {
        std::cerr << "Reached EOF!\n";
        break;
      }
    }

    my_value = values[0];

    std::cout << "Sending data\n";

    for (int i = 1; i < size; ++i) {
      MPI_Send(&values[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  } else {
    MPI_Status status;
    MPI_Recv(&my_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  std::stringstream ss;
  ss << "Value = " << my_value << ", Rank = " << rank << " / " << size << "\n";
  std::cout << ss.str();

  MPI_Finalize();
}