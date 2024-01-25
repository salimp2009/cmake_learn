#include "lambdabasics.hpp"
#include "lambdacaptures.hpp"
#include "lambdasort.hpp"
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace sp {

void lambda_basics1() noexcept {
  std::puts("-------------> lambda_basics1 test -------------<");
  SomeCaptures obj1{};
  auto result = obj1.double_val();
  fmt::println("Somecaptures: double_val: {}", result);
  std::puts("-------------> lambda_basics1 test passed -------------<");
}

void lambda_maps_sorted() noexcept {
  std::puts("-------------> lambda_maps_sorted test -------------<");
  map_books_sort_price();
  std::puts("-------------> lambda_maps_sorted test passed -------------<");
}

void lambda_variadic_args() noexcept {
  std::puts("-------------> lambda_variadic_args test -------------<");
  using namespace std::string_literals;
  auto logger = getNamedLogger("testing 1"s, "testing 2"s);
  logger("let us see"s, 50, 40);
  auto logger2 = getNamedLogger("testing 1"s, 45);
  logger2(455, "this works");
  std::puts("-------------> lambda_variadic_args test passed -------------<");
}
} // namespace sp
