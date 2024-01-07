#pragma once
#include "messageExport.h"
#include <cmath>
#include <limits>
#include <string>
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
