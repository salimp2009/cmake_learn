#include "compbasics.hpp"
#include "compstring.hpp"
#include <cstdio>
#include <fmt/core.h>

namespace sp {

void comp_basics1() noexcept {
  std::puts("-------------> comp_basics1 test -------------<");
  const char buffa[]{"Hello"};
  [[maybe_unused]] const char buffb[]{"Hello"};

  String stra{buffa};
  String strb{"somethng"};
  String strc{buffb};

  fmt::println("stra == strb [expected: false]: {}", stra == strb);
  fmt::println("stra > strb [expected: false]: {}", stra > strb);
  fmt::println("stra > strb [expected: true]: {}", stra < strb);
  fmt::println("stra == strc [expected: true]: {}", stra == strc);
  fmt::println("stra > strc [expected: false]: {}", stra > strc);
  fmt::println("stra < strc [expected: false]: {}", stra < strc);

  std::puts("-------------> comp_basics1 test passed -------------<");
}
} // namespace sp
