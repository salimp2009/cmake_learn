#include "sum_integers.hpp"
#include <numeric>

int sum_integers(std::span<const int> integers) {

  auto sum = std::accumulate(integers.begin(), integers.end(), 0);

  return sum;
}
