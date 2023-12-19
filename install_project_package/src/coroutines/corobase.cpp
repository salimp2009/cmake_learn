#include "corobase.hpp"
#include <fmt/core.h>

namespace sp {
IntGenerator coro_counter(int start, int end) {
  while (start < end) {
    co_yield start;
    ++start;
  }
}

void use_counter_value(int i) { fmt::print("value: {}\n", i); }

void use_coro_counter() {
  auto value = coro_counter(1, 5);
  for (const auto i : value) {
    use_counter_value(i);
  }
}

} // namespace sp
