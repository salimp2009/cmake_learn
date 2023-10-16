#include "sum_integers.hpp"
#include <numeric>
#include <span>
#include <vector>
// Creating and Running Tests Chapter 4
int sum_integers(const std::vector<int> &integers) {
  auto sum = 0;

  auto result = std::accumulate(std::begin(integers), std::end(integers), sum);
  return result;
}
