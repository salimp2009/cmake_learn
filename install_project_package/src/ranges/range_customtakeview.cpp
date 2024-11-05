#include "range_customtakeview.hpp"
#include <print>
#include <vector>
namespace sp {

void custom_take_check() {
  const std::vector<int> myvec{2, 3, 4, 5, 6, 7, 8, 9};
  auto result = myvec |
                std::views::filter([](auto &&val) { return val % 2 == 0; }) |
                sp::views::custom_take(7) | std::views::take(3);

  for (const auto &filterdresult : result)
    std::println("result from custom_take: {}", filterdresult);
}
} // namespace sp
