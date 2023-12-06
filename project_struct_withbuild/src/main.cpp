#include "print.hpp"
#include "sort.hpp"
#include "sum_vector.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
int main(int argc, const char **argv) {
  // std::vector<double> example = {4, 5.4, 9.1, 1, -2.2};
  // std::cout << "Before:\n";
  // myPrint(example);

  std::vector<double> commandline_args;
  std::ranges::transform(&argv[1], &argv[argc - 1],
                         std::back_inserter(commandline_args),
                         [](auto &&num) { return std::stod(num); });
  myPrint(commandline_args);
  mySort(commandline_args);
  myPrint(commandline_args);

  // mySort(example);
  // std::cout << "\nAfter:\n";

  // myPrint(example);

  // std::vector ins = {1, 2, 3, 4, 5};
  // auto result = sum_vector(ins);
  // std::cout << "sum vector:" << result << '\n';
  return 0;
}
