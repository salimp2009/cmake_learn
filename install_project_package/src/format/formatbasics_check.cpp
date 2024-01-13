#include "formatbasics.hpp"
#include "formatcolor.hpp"
#include "formatlog.hpp"
#include "stockindex.hpp"

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cstdio>
#include <format>
#include <iterator>
#include <locale>
#include <string>
#include <utility>
#include <vector>
// #include <cstddef>

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
                    "{0:#0o}, binary: {0:#0b}, character: {0:c}, string: "
                    "{1:s}, string: {1:.3s}",
                    'y', "hello");
  fmt::println("{}", res);
  const std::wstring ws2 = std::format(L"{}", L"K\u00F6ln");

  int number = 42;
  fmt::println("adress of number: {:p}, nullptr: {}",
               static_cast<void *>(&number), nullptr);
#ifdef _MSC_VER
  std::locale locG{"deu_deu.1252"};
#else
  std::locale locG{"en_US.UTF-8"};
#endif
  auto result_locale =
      std::format(locG, "normal locale: {0}, us locale: {0:L}", 1000.7);
  // this does not work on my computer
  // if it is different locale than below one
  fmt::println("{}", result_locale);

  std::puts("-------------> format_basics2 test passed -------------<");
}

void format_to_buffer() noexcept {
  std::puts("-------------> format_to_buffer test -------------<");
  char buffer[64];
  auto str = std::string{"hello str & format to"};
  auto result = std::format_to_n(buffer, std::size(buffer) - 1,
                                 "string {} has {} chars", str, std::size(str));
  *(result.out) = '\0';
  fmt::println("format_to_n: {}", buffer);
  std::puts("-------------> format_to_buffer test passed -------------<");
}

void print_indices() noexcept {
  std::puts("-------------> print_indices test -------------<");
  auto indices_vec = getindices();

  for (const auto &stock : indices_vec) {

    fmt::println("stockes indices: name: {:10}, points: {:>8.2f}, points diff: "
                 "{:>6.2f}, "
                 "points diff percent : {:.2f}",
                 stock.name(), stock.points(), stock.points_diff(),
                 stock.points_percent());

    auto result = std::format("{}", stock);
    fmt::println("using custom StockIndex formatter: {}", result);
  }
  std::locale locUS{"en_US.UTF-8"};
  std::locale::global(locUS);

  for (const auto &index : getindices()) {
    auto result = std::format(locUS, "{:Ls}", index);
    fmt::println("short format: {}", result);
  }

  for (const auto &index : getindices()) {
    auto result = std::format("{:Lp}", index);
    fmt::println("format withplus: {}", result);
  }

  auto result = std::format("{:>5.2Lf}", 100.7);
  fmt::println("locUS on regular types: {}", result);

  std::puts("-------------> print_indices test passed -------------<");
}

void color_test_hex() noexcept {
  std::puts("-------------> color_test_hex test -------------<");

  Color cool_colors{.r = 10, .g = 25, .b = 55};
  auto colorformat = std::format("{}", cool_colors);
  fmt::println("Color cool_colors: {}", colorformat);

  auto colorformat_hex = std::format("{0:h} {0:H}", cool_colors);
  fmt::println("Color cool_colors: {}", colorformat_hex);

  auto colorformat_hex2 = std::format("{0:h} {0:H}", Color{100, 200, 255});
  fmt::println("Color cool_colors: {}", colorformat_hex2);

  std::puts("-------------> color_test_hex test passed -------------<");
}

void custom_buffer() noexcept {
  std::puts("-------------> custom_buffer test -------------<");
  std::vector<char> buffer;
  constexpr const char *fmt = "{}, {}";
  std::format_to(std::back_inserter(buffer), fmt, "Hello", "Buffer");
  fmt::println("{}", buffer);

  // lookahead string size
  constexpr const char *fmt2{"{}, {}"};
  const auto size = std::formatted_size(fmt2, "Hello", "Buffer");
  std::vector<char> buffer2(size);
  std::format_to(buffer2.begin(), fmt2, "Hello", "Buffer");
  fmt::println("lookahead the formatted size: size: {},{} ", size, buffer2);

  // example for format_to_n
  std::array<char, 13> buffer3{};

  auto result = std::format_to_n(buffer3.data(), buffer3.size(), "{}, {}",
                                 "Hello", "World");
  *(result.out) = '\0';

  fmt::println("{}", buffer3);

  std::puts("-------------> custom_buffer test passed -------------<");
}

void logger_format() noexcept {
  std::puts("-------------> logger_format test -------------<");
  using enum LogLevel;
  // using namespace std::string_view_literals;
  fmt::println("{}", std::to_underlying(LogLevel::Info));
  // constexpr const char *fmt = "arg1: {}, arg2:{}";
  // logger(Info, fmt, "testing logger", "testing logger2");
  std::puts("-------------> logger_format test passed -------------<");
}
} // namespace sp
