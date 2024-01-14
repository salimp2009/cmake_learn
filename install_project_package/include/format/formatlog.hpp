#pragma once

#include <format>
#include <iostream>
#include <messageExport.h>
#include <source_location>
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
    // return std::format_to(ctx.out(), "{}",
    // LEVEL_NAMES[std::to_underlying(c)]);
  }
};

namespace sp {
template <typename... Args>
void logger(LogLevel level, std::string_view fmt, Args &&...args) {
  using namespace std::string_view_literals;

  std::clog << std::format("LOG LEVEL:{}, "sv, level)
            << std::vformat(fmt, std::make_format_args(args...)) << '\n';
};

struct message_EXPORT Logger {

  template <typename... Args>
  constexpr void operator()(
      LogLevel level, std::string_view fmt, Args &&...args
      /* std::source_location loc = std::source_location::current() */) const {
    using namespace std::string_view_literals;
    std::source_location loc = std::source_location::current();
    std::clog << std::format("LOG LEVEL:{}, location: {} "sv, level,
                             loc.file_name())
              << std::vformat(fmt, std::make_format_args(args...)) << '\n';
  }
};

// template <typename... Args> Logger(Args &&...) -> Logger<Args...>;

inline constexpr Logger log{};
} // namespace sp
