#pragma once

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <messageExport.h>
#include <source_location>
#include <string_view>
#include <strings.h>
#include <utility>

namespace sp {

enum class message_EXPORT LogLevel { Info, Warning, Error };

} // namespace sp

template <> struct std::formatter<sp::LogLevel> : std::formatter<const char *> {

  constexpr static const char *LEVEL_NAMES[] = {"Info", "Warning", "Error"};

  auto format(sp::LogLevel c, format_context &ctx) const {
    using enum sp::LogLevel;
    return std::formatter<const char *>::format(
        LEVEL_NAMES[std::to_underlying(c)], ctx);
  }
};

namespace sp {

template <std::size_t Args> constexpr auto make_braces() {
  constexpr std::array<char, 4> brace{"{} "};
  // size braces without '\0'
  constexpr auto brace_size = brace.size() - 1;
  // 2 chars for newline & '\0'
  constexpr auto offset = 2u;

  std::array<char, Args * brace_size + offset> braces{};
  constexpr auto bracesLength = brace_size - offset;

  auto indx = 0;
  std::for_each_n(braces.begin(), bracesLength, [&](auto &elem) {
    elem = brace[indx % brace_size];
    ++indx;
  });
  braces[bracesLength] = '\0';
  return braces;
}

void vlogger(LogLevel level, std::string_view fmt, std::format_args &&args);

template <typename... Args>
constexpr void logger(LogLevel level, std::string_view fmt, Args &&...args) {
  using namespace std::string_view_literals;

  vlogger(level, fmt, std::make_format_args(args...));
  // std::clog << std::format("LOG LEVEL:{}, "sv, level)
  //           << std::vformat(fmt, std::make_format_args(args...)) << '\n';
}

struct message_EXPORT Logger {

  template <typename... Args>
  constexpr void operator()(LogLevel level, std::string_view fmt,
                            Args &&...args) const {
    using namespace std::string_view_literals;
    std::clog << std::format("LOG LEVEL:{},  "sv, level)
              << std::vformat(fmt, std::make_format_args(args...)) << '\n';
  }
};

// template <typename... Args> Logger(Args &&...) -> Logger<Args...>;

message_EXPORT inline constexpr Logger log{};
} // namespace sp
