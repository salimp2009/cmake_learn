#include "coroStreamParser.hpp"
#include "corobase.hpp"
#include "corobasics.hpp"

#include <fmt/core.h>

namespace sp {

void coroutines_basics1() noexcept {
  std::puts("-------------> coroutines_basics1 test1 -------------<");
  use_coro_counter();
  fmt::print("Hello fmt\n");
  fmt::println("ESC from stream:{}", ESC);
  std::puts("-------------> coroutines_basics1 test1 passed -------------<");
}

void coroutines_stream() noexcept {
  std::puts("-------------> coroutines_stream test1 -------------<");
  simulate_stream();
  std::puts("-------------> coroutines_stream test1 passed -------------<");
}

} // namespace sp
