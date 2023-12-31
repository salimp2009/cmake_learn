#include "sum_integers.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <experimental/propagate_const>
#include <iomanip>
#include <ios>
#include <iostream>
#include <span>
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

  float data[1]{3.141592};
  auto const const_bytes = std::as_bytes(std::span{data});
  auto const writable_bytes = std::as_writable_bytes(std::span{data});
  writable_bytes[3] |= std::byte{0B1000'0000};
  for (auto const b : const_bytes) {
    std::cout << std::hex << std::uppercase << std::setfill('0') << std::setw(2)
              << std::to_integer<int>(b) << ' ';
  }
  std::cout << std::dec << '\n';
}
