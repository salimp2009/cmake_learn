#include "sum_integers.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
// we assume all arguments are integers and we sum them up
// for simplicity we do not verify the type of arguments
int main(int argc, const char *argv[]) {

  std::vector<int> integers;
  std::ranges::transform(&argv[1], &argv[argc], std::back_inserter(integers),
                         [](const auto &num) { return std::stoi(num); });

  std::cout << "integers:" << '\n';
  for (const auto &num : integers) {
    std::cout << num << '\n';
  }
  const auto sum = sum_integers(integers);

  std::cout << "sum of integers:" << sum << '\n';
}
