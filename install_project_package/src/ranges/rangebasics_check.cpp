#include "range_customtakeview.hpp"
#include "rangebase.hpp"
#include "rangebasics.hpp"

#include "fmt/ranges.h"
#include <fmt/core.h>
#include <format>
#include <numeric>
#include <print>
#include <ranges>
#include <vector>

namespace sp {

void range_basics1() noexcept {
  std::puts("-------------> coroutines_basics1 test1 -------------<");
  std::println("Hello range basic");

  const std::vector<int> numbers{2, 3, 4, 5, 6};

  fmt::println("fmt : {}", numbers);

  auto result = numbers |
                std::views::filter([](auto &&num) { return num % 2 == 0; }) |
                std::views::transform([](auto &&n) { return n * 2; });

  fmt::println("fmt result: {}", result);
  for (const auto &filteredresult : result)
    std::println("range result: {}", filteredresult);

  for (const auto &number : numbers)

    std::println("original numbers: {}", number);

  const std::vector<int> nums{5, 7, 4, 10};
  auto greater_than_five =
      nums | std::views::take_while([](auto &&x) { return x > 4; }) |
      std::views::common;

  for (const auto &greaterfives : greater_than_five)
    std::println("greater_than_five: {}", greaterfives);

  auto sum = std::accumulate(std::begin(greater_than_five),
                             std::end(greater_than_five), 0);
  std::println("sum (with common):{} ", sum);

  std::puts("-------------> coroutines_basics1 test1 passed -------------<");
}

void range_sort_projection() noexcept {
  sort_by_title();
  sort_by_isbn();
}

void range_add_currency() noexcept {
  std::puts("-------------> range_add_currency test1 -------------<");
  add_currency();
  std::vector<int> myvec{1, 2, 3, 4};
  std::puts("-------------> range_add_currency test1 passed -------------<");
}

void range_customs_views1() noexcept {
  std::puts("-------------> range_customs_views1 test1 -------------<");
  custom_take_check();
  std::puts("-------------> range_customs_views1 test1 passed -------------<");
}

} // namespace sp
