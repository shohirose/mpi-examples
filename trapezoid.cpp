#include <mpi.h>

#include <cstdio>
#include <iostream>
#include <utility>

/// @brief Integrates a function using the trapezoidal rule.
/// @tparam F Function type to be integrated
/// @param[in] x_low Lower limit of the integral interval
/// @param[in] x_low Upper limit of the integral interval
/// @param[in] n Number of bins
/// @param[in] f Function to be integrated
/// @returns Definite integral
template <typename F>
double integrate_using_trapezoidal_rule(double x_low, double x_high, int n,
                                        F&& f) {
  const auto h = (x_high - x_low) / n;
  double sum = 0;
  double x0 = x_low;
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

/// @brief Computes the integral range of the current process
std::pair<double, double> calc_my_range(int size, int rank) {
  const auto dx = 2.0 / size;
  const auto x_low = rank * dx - 1;
  const auto x_high = (rank + 1) * dx - 1;
  return std::make_pair(x_low, x_high);
}

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const auto [x_low, x_high] = calc_my_range(size, rank);
  const int n = 1000;
  const auto sum = integrate_using_trapezoidal_rule(
      x_low, x_high, n, [](double x) { return 2 / (1 + x * x); });

  double pi = 0.0;
  MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("intervals = %d, pi = %.16f\n", n, pi);
  }

  MPI_Finalize();
}