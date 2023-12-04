// this tells catch to provide a main()
// only do this in one cpp file
// #include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <vector>

#include <Message.hpp>
#include <conceptbasics.hpp>

uint32_t factorial(uint32_t number) {
  return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(factorial(1) == 1);
  REQUIRE(factorial(2) == 2);
  REQUIRE(factorial(3) == 6);
  REQUIRE(factorial(10) == 3'628'800);
}

TEST_CASE("checking are_same_v type trait", "[short]") {
  static_assert(not sp::are_same_v<decltype(1), decltype(2.4)>);
  static_assert(not are_same2<decltype(1), decltype(2.4)>);
  REQUIRE(sp::are_same_v<decltype(1), decltype(2)>);
}
