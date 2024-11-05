#include "compbasics.hpp"
#include "compstring.hpp"
#include <cstdio>
#include <print>

namespace sp {

void comp_basics1() noexcept {
  std::puts("-------------> comp_basics1 test -------------<");
  const char buffa[]{"Hello"};
  [[maybe_unused]] const char buffb[]{"Hello"};

  String stra{buffa};
  String strb{"somethng"};
  String strc{buffb};

  std::println("stra == strb [expected: false]: {}", stra == strb);
  std::println("stra > strb [expected: false]: {}", stra > strb);
  std::println("stra > strb [expected: true]: {}", stra < strb);
  std::println("stra == strc [expected: true]: {}", stra == strc);
  std::println("stra > strc [expected: false]: {}", stra > strc);
  std::println("stra < strc [expected: false]: {}", stra < strc);

  std::puts("-------------> comp_basics1 test passed -------------<");
}
} // namespace sp
