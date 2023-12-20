#include "coroStreamParser.hpp"
#include "corobase.hpp"
#include "corobasics.hpp"

#include <fmt/core.h>

namespace sp {

void coroutines_basics1() noexcept {
  std::puts("-------------> coroutines_basics1 test1 -------------<");
  use_coro_counter();
  fmt::print("Hello fmt\n");
  std::puts("-------------> coroutines_basics1 test1 passed -------------<");
}
} // namespace sp
