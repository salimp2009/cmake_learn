#pragma once

#include "messageExport.h"
#include <fmt/core.h>

#include <format>
#include <string>

namespace sp {
struct Book {
  std::string title{};
  std::string isbn{};
};

message_EXPORT void sort_by_title();
message_EXPORT void sort_by_isbn();
message_EXPORT void add_currency();
} // namespace sp

// std::formatter customization has to either in namespace st or global
template <> struct std::formatter<sp::Book> {
  formatter() = default;
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const sp::Book &obj, std::format_context &ctx) const {
    auto title = obj.title;
    auto isbn = obj.isbn;
    return std::format_to(ctx.out(), "{}, {}", title, isbn);
  }
};

// fmt::formatter customization has to either in namespace st or global
template <> struct fmt::formatter<sp::Book> {
  formatter() = default;
  constexpr auto parse(fmt::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const sp::Book &obj, fmt::format_context &ctx) const {
    auto title = obj.title;
    auto isbn = obj.isbn;
    return fmt::format_to(ctx.out(), "{}, {}", title, isbn);
  }
};
