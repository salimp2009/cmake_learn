#include "stlbasics.hpp"

// #include <bit>
#include <array>
#include <chrono>
#include <complex>
#include <cstdint>
#include <ctime>
// #include <experimental/memory>
#include "fmt/core.h"
#include <algorithm>
#include <cstdint>
#include <execution>
#include <format>
#include <iterator>
#include <locale>
#include <memory>
#include <print>
#include <span>
#include <stdfloat>
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
  __uint128_t my128int = 100000000000000000;
  std::println("__uint128 supported: {}", my128int);

  // this make an shared_ptr<[4][3][4]>
  auto mysharedptr = std::make_shared<int[][3][4]>(4);

  constexpr int aa2[]{0, 1, 2, 3, 4, 5, 6, 7, 8};
  constexpr static std::size_t width{6};

  for (std::size_t offset{}; offset < std::size(aa2); ++offset)
    if (auto s = slide(std::span{aa2}, offset, width); !s.empty())
      fmt::println("span: {}", s);

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
  const int myvar = 56;
  test(myvar);
  // alignas(std::complex<float>) unsigned char network_data[sizeof(
  //     std::complex<float>)]{0xcd, 0xcc, 0xcc, 0x3d, 0xcd, 0xcc, 0x4c, 0x3e};
  // auto d = *std::start_lifetime_as<std::complex<float>>(network_data);

  std::vector vv = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::rotate(std::execution::par, vv.begin(), std::ranges::next(vv.begin(), 5),
              vv.end());
  fmt::println("rotated vector: {}", vv);

  fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
                 fmt::emphasis::underline,
             "Olá, {}!\n", "Mundo");
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic, "你好{}！\n",
             "世界");
  std::println("你好{}!", "世界🚀");
  testextern<float>();
  using namespace std::literals;
  constexpr auto wchar = L"wchar_t ∀"sv;
  std::wcout << wchar << '\n';
  std::wstring wbuffer;
  std::format_to(std::back_inserter(wbuffer), // < OutputIt
                 L"Hello, {}, wchar {}",      // < fmt
                 L"wchar_t ∀", wchar          // < unused
  );
  std::wcout << wbuffer << '\n';
  auto my_wstring = std::format(L"Hello, {}, wchar {}", L"wchar_t ∀", wchar);
  // wstring does not work with std::print or fmt::print.
  // Only works std::wcout
  std::printf("%ls\n", my_wstring.data());
  std::println("banana const char[5] = {}", "🍌");

  using fp16_t = _Float16;

  fp16_t my_flt = 16.0f16;
  std::print("float16_t {:f}\n", static_cast<float>(my_flt));
  // pack indexing C++26; gcc 15
  int px = [](auto &&...x) -> int { return x...[2]; }(0, 1, 2);
  std::println("pack index [2]: {}", px);

  std::puts("-------------> local_time_basics test1 passed -------------<");
}

} // namespace sp
