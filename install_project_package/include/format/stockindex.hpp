#pragma once
#include "messageExport.h"

// #include <cmath>
#include <format>
// #include <limits>
#include <string>
#include <strings.h>
#include <vector>

namespace sp {

class message_EXPORT StockIndex {
  std::string m_name;
  double m_lastpoints{};
  double m_points{};

public:
  constexpr explicit StockIndex(std::string name) : m_name{std::move(name)} {}
  const std::string &name() const & { return m_name; }

  constexpr void set_points(double points) {
    m_lastpoints = m_points;
    m_points = points;
  }

  constexpr double points() const & { return m_points; }
  constexpr double points_diff() const & { return m_points - m_lastpoints; }
  constexpr double points_percent() const & {
    // auto machine_epsilon = std::numeric_limits<double>::epsilon();
    if (m_lastpoints == 0.0 /* + machine_epsilon */) {
      return 0.0;
    }
    return (m_points - m_lastpoints) / m_lastpoints * 100;
  }
};

message_EXPORT std::vector<StockIndex> getindices();

} // namespace sp

// template <> struct std::formatter<sp::StockIndex> {
//   formatter() = default;

//   constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin();
//   }

//   auto format(const sp::StockIndex &index, std::format_context &ctx) const {
//     return std::format_to(ctx.out(),
//                           "name: {:10}, points: {:>8.2f}, point diff: "
//                           "{:>6.2f}, points percent: {:.2f}%",
//                           index.name(), index.points(), index.points_diff(),
//                           index.points_percent());
//   }
// };

template <> struct std::formatter<sp::StockIndex> {
  enum class IndexFormat { Normal, Short, WithPlus };

  IndexFormat index_format{IndexFormat::Normal};
  bool localized = false;

  constexpr auto parse(std::format_parse_context &ctx) {
    auto it = ctx.begin();

    // #B Helper to search for a character
    auto isChar = [&](char c) {
      if ((it != ctx.end()) && (*it == c)) {
        ++it;
        return true;
      }

      return false;
    };

    // #C Localized formatting
    if (isChar('L')) {
      localized = true;
    }

    if (isChar('s')) {
      index_format = IndexFormat::Short;
    } else if (isChar('p')) {
      index_format = IndexFormat::WithPlus;
    }

    if (it != ctx.end() && *it != '}') {
      throw format_error("invalid format");
    }

    return it;
  }

  auto format(const sp::StockIndex &index, std::format_context &ctx) const {
    using enum IndexFormat;
    using namespace std::string_literals;

    // #D Add localized
    const auto locFloat{localized ? "L"s : ""s};
    const auto plus{(IndexFormat::WithPlus == index_format) ? "+"s : ""s};

    if (IndexFormat::Short == index_format) {
      const auto fmt = std::format("{{:10}} {{:>8.2{}f}}"sv, locFloat);

      return std::vformat_to(
          ctx.out(), fmt, std::make_format_args(index.name(), index.points()));

    } else {
      const auto fmt{std::format("{{:10}} {{:>8.2{0}f}}  {{:>{1}7.2{0}f}} "
                                 "{{:{1}.2{0}f}}%"sv,
                                 locFloat, plus)};

      return std::vformat_to(ctx.out(), fmt,
                             std::make_format_args(index.name(), index.points(),
                                                   index.points_diff(),
                                                   index.points_percent()));
    }
  }
};

//   auto format(const sp::StockIndex &index, std::format_context &ctx) const {
//     using enum IndexFormat;

//     switch (index_format) {
//     case Short: {
//       return std::format_to(ctx.out(), "name: {:10}, points:{:>8.2f}",
//                             index.name(), index.points());
//     }
//     case WithPlus: {
//       return std::format_to(ctx.out(), "{:10} {:>8.2f} {: >+7.2f} {:+.2f}%",
//                             index.name(), index.points(),
//                             index.points_diff(), index.points_percent());
//     }
//     case Normal: {
//       return std::format_to(ctx.out(), "{:10}, {:>8.2f}, {:>7.2f}, {:.2f}%",
//                             index.name(), index.points(),
//                             index.points_diff(), index.points_percent());
//     }
//     }

//     return std::format_to(ctx.out(), "{:10}, {:>8.2f}, {:>7.2f}, {:.2f}%",
//                           index.name(), index.points(), index.points_diff(),
//                           index.points_percent());
//   }
// };
