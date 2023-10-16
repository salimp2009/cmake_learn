#include <numeric>
#include <ranges>
#include <span>
#include <sum_vector.hpp>
int sum_vector(std::span<const int> integers) {
  auto result = std::accumulate(std::begin(integers), std::end(integers), 0);
  return result;
}
