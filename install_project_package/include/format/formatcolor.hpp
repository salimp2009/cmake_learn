#pragma once

#include "messageExport.h"

#include <cstdint>
#include <format>

namespace sp {

struct message_EXPORT Color {
  std::uint8_t r{0};
  std::uint8_t g{0};
  std::uint8_t b{0};
};
} // namespace sp

template <> struct std::formatter<sp::Color> {
  bool isHex{false};

  constexpr auto parse(std::format_parse_context &ctx) {
    auto pos = ctx.begin();
    while (pos != ctx.end() && *pos != '}') {
      switch (*pos) {
      case 'h':
      case 'H':
        isHex = true;
        ++pos;
        break;
      }
    }

    return pos;
  }

  auto format(const sp::Color &col, std::format_context &ctx) const {
    if (isHex) {
      std::uint32_t val = col.r << 16 | col.g << 8 | col.b;
      return std::format_to(ctx.out(), "#{:x}", val);
    }
    return std::format_to(ctx.out(), "({}, {}, {})", col.r, col.g, col.b);
  }
};
