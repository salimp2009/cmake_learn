#include "rangebase.hpp"
#include "rangebasics.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <numeric>
#include <ranges>
#include <vector>

namespace sp {

void range_basics1() noexcept {
  std::puts("-------------> coroutines_basics1 test1 -------------<");
  fmt::println("Hello range basic");

  const std::vector<int> numbers{2, 3, 4, 5, 6};

  auto result = numbers |
                std::views::filter([](auto &&num) { return num % 2 == 0; }) |
                std::views::transform([](auto &&n) { return n * 2; });

  fmt::println("range result: {}", result);
  fmt::println("original numbers: {}", numbers);

  const std::vector<int> nums{5, 7, 4, 10};
  auto greater_than_five =
      nums | std::views::take_while([](auto &&x) { return x > 4; }) |
      std::views::common;

  fmt::println("greater_than_five: {}", greater_than_five);

  auto sum = std::accumulate(std::begin(greater_than_five),
                             std::end(greater_than_five), 0);
  fmt::println("sum (with common):{} ", sum);

  std::puts("-------------> coroutines_basics1 test1 passed -------------<");
}

void range_sort_projection() noexcept {
  sort_by_title();
  sort_by_isbn();
}

} // namespace sp
