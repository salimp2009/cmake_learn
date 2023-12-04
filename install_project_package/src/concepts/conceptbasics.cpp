
#include "conceptbasics.hpp"
// #include "messageExport.h"
#include <cstdio>

namespace message_NO_EXPORT sp {

static_assert(not are_same_v<decltype(1), decltype(2.4)>);

int Test::get_value() const { return value; }

int getnumber() { return 5; }

void concepts_test1() noexcept {
  std::puts("-------------> concepts test1-------------<");
  auto result = sp::myadd(5.4, 5, 6.4, 100);
  std::cout << "result: " << result << '\n';

  // example using std::enable_if_t to use it pre C++17 & 20
  auto result2 = sp::add_sametypes(5.4, 4.5, 20.);
  auto result3 = sp::add_sametypes(5, 4, 20);

  static_assert(std::is_same_v<decltype(result3), int>);
  static_assert(std::is_same_v<decltype(result2), double>);

  static_assert(std::is_same_v<decltype(result), double>);

  constexpr auto result4 = sp::add_sametypes2(1, 2, 3);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result4)>, int>);

  constexpr auto result5 = sp::add_sametypes2(1., 2.4, 3.);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result5)>, double>);
  std::puts("-------------> concepts test1 passed-------------<");
}
} // namespace message_NO_EXPORT sp
