#include "formatbasics.hpp"
#include <cstddef>
#include <cstdio>
#include <fmt/core.h>
#include <fmt/format.h>
#include <format>
#include <locale>
#include <string>
namespace sp {

void format_basics1() noexcept {
  std::puts("-------------> format_basics1 test1 -------------<");
  // this is need to make "xcvcxvc"s work
  using namespace std::string_literals;

  auto result = std::format("{:>10} {:>8.2f} {:>6.2f} {:.2f}% {} \n",
                            "first string", 5.456, 7.34345, 1.4345, 1.3435);
  fmt::println("{}", result);

  [[maybe_unused]] const double pi = 3.14;
  [[maybe_unused]] const int i = 1'024;

  // const auto locDE = std::locale("de_DE.UTF-8"s);
  const auto locUS = std::locale("en_US.UTF-8"s);

  std::puts("-------------> format_basics1 test1 passed -------------<");
}

} // namespace sp
