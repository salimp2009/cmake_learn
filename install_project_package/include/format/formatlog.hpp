#pragma once

#include <format>
#include <iostream>
#include <messageExport.h>
#include <source_location>
#include <utility>
namespace sp {

enum class message_EXPORT LogLevel { Info, Warning, Error };

template <typename... Args>
void logger(LogLevel level, const std::string_view fmt, const Args &...args) {
  std::cout << std::format("log level:{}", std::to_underlying(level))
            << std::format(fmt, args...) << '\n';
};

} // namespace sp

// template <> struct std::formatter<sp::LogLevel> : std::formatter<const char
// *> {
//   constexpr static const char *LEVEL_NAMES[] = {"Info", "Warning", "Error"};
//   auto format(sp::LogLevel c, format_context &ctx) {
//     using enum sp::LogLevel;
//     return std::formatter<const char *>::format(
//         LEVEL_NAMES[std::to_underlying(c)], ctx);
//   }
// };
