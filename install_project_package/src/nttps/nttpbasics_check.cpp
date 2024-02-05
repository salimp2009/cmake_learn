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
  print(format_string<"%s, %s, %a\n">{}, "Hellooo safe printf",
        "testing safe printf", 56.7);

  print("%s, %s %#x\n"_fs, "user defined", "literal works", 56);
  constexpr auto match_result = match<void *>('p');
  static_assert(match_result == true);

  constexpr auto match_result2 = match<char>('#');
  static_assert(match_result2 == false);

  constexpr auto match_result3 = match<int>('#');
  static_assert(match_result3 == true);

  constexpr auto match_result4 = match<double>('a');
  static_assert(match_result4 == true);

  constexpr auto match_result5 = match<double>('X');
  static_assert(match_result5 == false);

  constexpr auto match_result6 = match<double>('x');
  static_assert(match_result6 == false);

  constexpr auto match_result7 = match<char>('x');
  static_assert(match_result7 == false, "expected:false");

  print(format_string<"%s, %s\n">{}, "Hello", "C++20");

  // this uses safe print version
  print("%s, %s\n"_fs, "Hello", "C++20 uses safe print");

  // example that uses char*; not so safe
  char fmt[]{"Hello, %s\n"};
  print(fmt, "C++20");

  // this tries to use const char*; does not work & unsafe
  // print("%s\n", "const char* does not work");
  std::puts("-------------> safe_printf test  passed -------------<");
}

} // namespace sp
