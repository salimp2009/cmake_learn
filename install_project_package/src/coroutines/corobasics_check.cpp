#include "coroDataStreamReader.hpp"
#include "coroStreamParser.hpp"
#include "corobase.hpp"
#include "corobasics.hpp"
#include "coropromise_custom_alloctr.hpp"

#include <cstddef>
#include <optional>
#include <print>
#include <type_traits>
#include <vector>

namespace sp {

void coroutines_basics1() noexcept {
  std::puts("-------------> coroutines_basics1 test1 -------------<");
  use_coro_counter();
  std::print("Hello std::print\n");
  std::println("ESC from stream:{}", static_cast<char>(ESC));
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
  std::println("Debug Build is On");
#else
  std::println("Release Build is On");
#endif // DEBUG
  std::puts("-------------> coroutines_stream_v2 test1 passed -------------<");
}

void coroutines_stream_allocator() noexcept {
  std::puts("-------------> coroutines_stream_v2 test1 -------------<");
  stream_simulator_arena_alloc();
  std::puts("-------------> coroutines_stream_v2 test1 passed -------------<");
}

} // namespace sp
