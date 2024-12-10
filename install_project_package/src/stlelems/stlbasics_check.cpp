#include "stlbasics.hpp"

// #include <bit>
#include <chrono>
// #include <complex>
#include <cstdint>
#include <ctime>
// #include <experimental/memory>
// #include <memory>
#include "fmt/core.h"
#include <ostream>
#include <print>
#include <type_traits>
#include <variant>

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

  std::variant<std::string, int, char> var{"salitos"};
  std::get_if<std::string>(&var);

  Vector vc{2, -1};
  std::println("x: {}, y:{}", vc.X, vc.Y);
  vc.Print();
  // FloatOrInt uu{aa};

  testextern<int>();
  testextern<float>();
  testextern<int>();

  fmt::println("testing fmt in stlelems {}", "works");

  std::puts("-------------> stlchanges_basics1 test1 passed -------------<");
}

void time_zone_basics1() noexcept {
  std::puts("-------------> time_zone_basics1 test1 -------------<");

  const auto now = std::chrono::floor<std::chrono::minutes>(
      std::chrono::system_clock::now());
  auto zonetime_loc = std::chrono::zoned_time{"Europe/Istanbul", now};
  std::println("now is {} UTC and Istanbul is {}", now, zonetime_loc);
  const auto time =
      std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
  const auto now_local = std::chrono::floor<std::chrono::minutes>(time);

  std::println("now is {} UTC and Current Location is {}", now, now_local);
  std::puts("-------------> time_zone_basics1 test1 passed -------------<");
}
void local_time_basics() noexcept {
  std::puts("-------------> local_time_basics test1 -------------<");
  print_zone_time(std::chrono::year{2024} / 13 / 14, "Europe/Istanbul");
  std::puts("-------------> local_time_basics test1 passed -------------<");
  const int myvar = 56;
  test(myvar);
  // alignas(std::complex<float>) unsigned char network_data[sizeof(
  //     std::complex<float>)]{0xcd, 0xcc, 0xcc, 0x3d, 0xcd, 0xcc, 0x4c, 0x3e};
  // auto d = *std::start_lifetime_as<std::complex<float>>(network_data);
}

} // namespace sp
