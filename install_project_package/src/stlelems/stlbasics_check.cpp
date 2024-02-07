#include "stlbasics.hpp"

#include <bit>
#include <cstdint>

#include <fmt/core.h>

namespace sp {

void stlchanges_basics1() noexcept {
  std::puts("-------------> stlchanges_basics1 test1 -------------<");
  const float myfloat = 3.15f;
  fmt::print("myfloat by using bit_cast: {}\n", myfloat);

  const std::uint32_t myint32 = std::bit_cast<std::uint32_t>(myfloat);
  fmt::print("myint32 by using bit_cast: {}\n", myint32);

  constexpr double mydouble = 19880124.0;
  fmt::print("mydouble by using bit_cast: {}\n", mydouble);
  constexpr auto myuint = std::bit_cast<std::uint64_t>(mydouble);
  fmt::print("myuint by using bit_cast: {}\n", myuint);

  std::puts("-------------> stlchanges_basics1 test1 passed -------------<");
}

} // namespace sp
