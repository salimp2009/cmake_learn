#include "formatbasics.hpp"

#include <fmt/core.h>
#include <fmt/format.h>

#include <format>
#include <string>

#include <cstdio>
#include <locale>

namespace sp {

void format_basics1() noexcept {
  std::puts("-------------> format_basics1 test -------------<");
  // this is needed to make "xcvcxvc"s work
  using namespace std::string_literals;

  auto result = std::format("{:>10} {:>8.2f} {:>6.2f} {:.2f}% {} \n",
                            "first string", 5.456, 7.34345, 1.4345, 1.3435);
  fmt::println("{}", result);

  [[maybe_unused]] const double pi = 3.14;
  [[maybe_unused]] const int i = 1'024;

  // const auto locDE = std::locale("de_DE.UTF-8"s);
  const auto locUS = std::locale("en_US.UTF-8"s);

  result = std::format("{:*<7}", 42);
  fmt::println("{}", result);

  result = std::format("{:*>7}", 42);
  fmt::println("{}", result);

  result = std::format("{:*^8}", 42);
  fmt::println("{}", result);
  fmt::println("typeid.name :{}", typeid(decltype(locUS)).name());
  std::puts("-------------> format_basics1 test passed -------------<");
}

void format_basics2() noexcept {
  std::puts("-------------> format_basics2 test -------------<");

  auto res = std::format("{0} has value hex: {0:0X}, decimal: {0:+4d}, octal: "
                         "{0:0o}, binary: {0:0b}",
                         '?');
  fmt::println("{}", res);

  res = std::format("{0} has value hex: {0:#0x}, decimal: {0:+4d}, octal: "
                    "{0:#0o}, binary: {0:#0b}",
                    'y');
  fmt::println("{}", res);

  std::puts("-------------> format_basics2 test passed -------------<");
}

void format_to_buffer() noexcept {
  std::puts("-------------> format_to_buffer test -------------<");

  std::puts("-------------> format_to_buffer test passed -------------<");
}

} // namespace sp
