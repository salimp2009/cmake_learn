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
  constexpr std::array<char, 4u> brace{"{} "};
  // size braces without '\0'
  constexpr auto brace_size = brace.size() - 1u;
  // 2 chars for newline & '\0'
  constexpr auto offset = 2u;

  std::array<char, Args * brace_size + offset> braces{};
  constexpr auto bracesLength = (braces.size() - offset);

  auto indx = 0u;
  std::for_each_n(braces.begin(), bracesLength, [&](auto &elem) {
    elem = brace[indx % brace_size];
    ++indx;
  });
  braces[bracesLength] = '\n';
  return braces;
}

void vlogger(LogLevel level, std::string_view fmt, std::format_args &&args);

template <typename... Args>
constexpr void logger(LogLevel level, Args &&...args) {
  using namespace std::string_view_literals;

  constexpr auto braces = make_braces<sizeof...(Args)>();

  vlogger(level, std::string_view{braces.data()},
          std::make_format_args(std::forward<Args>(args)...));
}

struct FormatWithLocation {
  LogLevel mlevel{};
  std::source_location mloc{};

  constexpr FormatWithLocation(
      LogLevel lvl,
      const std::source_location &l = std::source_location::current())
      : mlevel{lvl}, mloc{l} {}
};

struct message_EXPORT Logger {

  template <typename... Args>
  constexpr void operator()(FormatWithLocation levloc, std::string_view fmt,
                            Args &&...args) const {
    using namespace std::string_view_literals;
    std::clog
        << std::format(
               "LOG LEVEL:{}, called from [function: {}, line: {}] [in file: {}]\n "sv,
               levloc.mlevel, levloc.mloc.function_name(), levloc.mloc.line(),
               levloc.mloc.file_name())
        << std::vformat(fmt, std::make_format_args(args...)) << '\n';
  }
};

message_EXPORT inline constexpr Logger log{};
} // namespace sp
