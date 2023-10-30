// this tells catch to provide a main()
// only do this in one cpp file
// #include <catch2/catch_all.hpp>
#include "sort.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <vector>

uint32_t factorial(uint32_t number) {
  return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(factorial(1) == 1);
  REQUIRE(factorial(2) == 2);
  REQUIRE(factorial(3) == 6);
  REQUIRE(factorial(10) == 3'628'800);
}

TEST_CASE("sorting a vector of double", "[short]") {
  std::vector<double> integers = {1, 5, 9, 4, 3};
  mySort(integers);
  REQUIRE(integers == std::vector<double>({1, 3, 4, 5, 9}));
}
