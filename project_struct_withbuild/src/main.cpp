#include <iostream>

#include "print.hpp"
#include "sort.hpp"
#include "sum_vector.hpp"
#include <glib-2.0/glib.h>

int main() {
  std::vector<double> example = {4, 5.4, 9.1, 1, -2.2};
  std::cout << "Before:\n";
  myPrint(example);

  mySort(example);
  std::cout << "\nAfter:\n";
  myPrint(example);
  std::vector ins = {1, 2, 3, 4, 5};
  auto result = sum_vector(ins);
  std::cout << "sum vector:" << result << '\n';
  return 0;
}
