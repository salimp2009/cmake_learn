// #include <print>
#include "print.hpp"
#include "sort.hpp"
#include <sum_vector.hpp>
#include <vector>

int main() {

  [[maybe_unused]] std::vector<double> v = {2, 3, 1, 7, 5, 8, 9, 7, 0};
  mySort(v);
  myPrint(v);
}
