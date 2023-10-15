#include <iostream>

#include "print.hpp"
#include "sort.hpp"

int main(int argc, char **argv) {
  std::vector<double> example = {4, 5.4, 9.1, 1, -2.2};
  std::cout << "Before:\n";
  myPrint(example);

  mySort(example);

  std::cout << "\nAfter:\n";
  myPrint(example);
  return 0;
}
