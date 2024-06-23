#include "aggregbasics.hpp"
#include <fmt/core.h>
#include <memory>
// #include <print>

namespace sp {

void aggregate_basics1() noexcept {
  std::puts("-----> aggregate_basics1 test ------<");
  const auto point3d = Point3D{.x = 1, .y = 4, .z = 5};
  // std::print("3d point: {}, {}, {}\n", point3d.x, point3d.y, point3d.z);

  const auto point3d_ptr = std::make_unique<Point3D>(4, 5, 10);
  fmt::print("Point3D pointer: x={}\n", point3d_ptr->x);
  Point3D point3d_2(2, 3, 4);
  fmt::print("point3d_2 => {}, {}, {}\n", point3d_2.x, point3d_2.y,
             point3d_2.z);

  // LifetimeExtension lifetime_ext1{3};

  // Dangling refrence ?
  // LifetimeExtension lifetime_ext2(4);

  // fmt::println("lifetime_ext1: {}", lifetime_ext1.rval);

  // this prints 1 which is a garbage value!!
  // fmt::print("lifetime_ext2: {}\n", lifetime_ext2.rval);

  // since C++20 this does not compile since default constructor is deleted
  // it used to compile before C++20
  // NotDefaultConstructible notdefconst_1{};

  std::puts("-------------> aggregate_basics1 test passed -------------<");
}

} // namespace sp
