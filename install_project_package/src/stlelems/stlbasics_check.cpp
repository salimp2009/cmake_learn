#include "stlbasics.hpp"

#include <bit>
#include <cstdint>
#include <print>
#include <type_traits>

namespace sp {

void stlchanges_basics1() noexcept {
  std::puts("-------------> stlchanges_basics1 test1 -------------<");
  const float myfloat = 3.15f;
  std::print("myfloat by using bit_cast: {}\n", myfloat);

  const std::uint32_t myint32 = std::bit_cast<std::uint32_t>(myfloat);
  std::print("myint32 by using bit_cast: {}\n", myint32);

  constexpr double mydouble = 19880124.0;
  std::print("mydouble by using bit_cast: {}\n", mydouble);
  constexpr auto myuint = std::bit_cast<std::uint64_t>(mydouble);
  std::print("myuint by using bit_cast: {}\n", myuint);

  float pi = 3.14f;
  // static cast from float to uint32 not work as intended
  // see below union FloatOrInt still initialized as float
  const auto a = static_cast<uint32_t>(pi);
  std::println("{:10d}", a);

  FloatOrInt u{pi};
  static_assert(std::is_same_v<decltype(u), decltype(FloatOrInt{0.0f})>);

  const uint32_t aa = std::bit_cast<uint32_t>(pi);
  std::println("{}", aa);
  // FloatOrInt uu{aa};
  std::puts("-------------> stlchanges_basics1 test1 passed -------------<");
}

} // namespace sp
