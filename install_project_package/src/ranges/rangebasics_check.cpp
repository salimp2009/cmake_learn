#include "rangebasics.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
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

  std::puts("-------------> coroutines_basics1 test1 passed -------------<");
}

} // namespace sp
