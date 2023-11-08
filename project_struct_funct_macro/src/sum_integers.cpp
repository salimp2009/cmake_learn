#include "sum_integers.hpp"
#include <numeric>
#include <vector>

int sum_integers(std::span<const int> integers) {
  return std::accumulate(std::begin(integers), std::end(integers), 0);
}
