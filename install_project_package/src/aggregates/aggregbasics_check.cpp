#include "aggregbasics.hpp"
#include <fmt/core.h>

namespace sp {

void aggregate_basics1() noexcept {
  std::puts("-------------> aggregate_basics1 test -------------<");
  const auto point3d = Point3D{.y = 4, .z = 5};
  fmt::print("3d point: {}, {}, {}\n", point3d.x, point3d.y, point3d.z);
  std::puts("-------------> aggregate_basics1 test passed -------------<");
}

} // namespace sp
