#include "coroDataStreamReader.hpp"
#include "coroStreamParser.hpp"
#include "corobase.hpp"
#include "corobasics.hpp"
#include "coropromise_custom_alloctr.hpp"

#include <fmt/core.h>
#include <optional>
#include <type_traits>
#include <vector>

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

void coroutines_stream_v2() noexcept {
  std::puts("-------------> coroutines_stream_v2 test1 -------------<");
  stream_simulator2();
#if DEBUG
  fmt::println("Debug Build is On");
#else
  fmt::println("Release Build is On");
#endif // DEBUG
  std::puts("-------------> coroutines_stream_v2 test1 passed -------------<");
}

void coroutines_stream_allocator() noexcept {
  std::puts("-------------> coroutines_stream_v2 test1 -------------<");
  stream_simulator_arena_alloc();
  std::puts("-------------> coroutines_stream_v2 test1 passed -------------<");
}

} // namespace sp
