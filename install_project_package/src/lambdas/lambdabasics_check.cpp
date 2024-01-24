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
} // namespace sp
