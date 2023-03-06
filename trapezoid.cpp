#include <fmt/core.h>
#include <mpi.h>

#include <cstdio>

struct Range {
  Range(double low_, double high_) : low{low_}, high{high_} {}

  double low;
  double high;
};

/// @brief Integrates a function using the trapezoidal rule.
/// @tparam F Function type to be integrated
/// @param[in] rng Integral range
/// @param[in] n Number of bins
/// @param[in] f Function to be integrated
/// @returns Definite integral
template <typename F>
double integrate(Range rng, int n, F&& f) {
  const auto h = (rng.high - rng.low) / n;
  double sum = 0;
  double x0 = rng.low;
  double x1 = x0 + h;
  for (int i = 0; i < n; ++i) {
    const auto f0 = f(x0);
    const auto f1 = f(x1);
    sum += 0.5 * (f0 + f1) * h;
    x0 = x1;
    x1 += h;
  }
  return sum;
}

/**
 * @brief Gets the integral range of the current process
 * 
 * @param size Number of processes
 * @param rank Process ID
 * @return Integral range
 */
Range get_range(int size, int rank) {
  const auto dx = 2.0 / size;
  const auto low = rank * dx - 1;
  const auto high = (rank + 1) * dx - 1;
  return {low, high};
}

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const auto rng = get_range(size, rank);
  const int n = 1000;
  const auto sum = integrate(
      rng, n, [](double x) { return 2 / (1 + x * x); });

  double pi = 0.0;
  MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    fmt::print("intervals = {}, pi = {:.10f}\n", n, pi);
  }

  MPI_Finalize();
}