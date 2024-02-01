#include "fixedstring.hpp"
#include "nttpbasics.hpp"

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <type_traits>

namespace sp {
void nttp_basics1() noexcept {
  std::puts("-------------> nttp_basics1 test -------------<");

  sp::Array<int, 5> myarray{5, 4, 3, 5};
  static_assert(std::is_same_v<decltype(myarray.data), int[5]>);
  fmt::println("myaray: {}", myarray.data);
  // NOLINTNEXTLINE
  // static_assert(std::is_same_v<Doubles<+0.3 + 0.1>, Doubles<0.4>>); // NOLINT

  fixed_string fs{"Hello World"};
  static_assert(std::is_same_v<decltype(fs.data), char[sizeof fs]>);

  fixed_string_container<"Hello fixed string container"> fxcont{};
  fxcont.print();
  std::puts("-------------> nttp_basics1 test passed -------------<");
}

void safe_printf() noexcept {
  std::puts("-------------> safe_printf test -------------<");
  // incomplete; need to verify
  print(format_string<"%s, %s\n">{}, "Hellooo safe printf",
        "testing safe printf");

  print("%s, %s\n"_fs, "user defined", "literal works");
  constexpr auto match_result = match<void *>('p');
  static_assert(match_result == true);

  std::puts("-------------> safe_printf test passed -------------<");
}

} // namespace sp
