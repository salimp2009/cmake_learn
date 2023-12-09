#include "conceptbasics_check.hpp"
#include "conceptconstexpr.hpp"
#include "conceptmoptional.hpp"
#include "conceptteststub.hpp"
#include "conceptvalidation.hpp"
#include <array>

namespace sp {

void concepts_basics1() noexcept {
  std::puts("-------------> concepts test1 -------------<");
  auto result = sp::myadd(5.4, 5, 6.4, 100);
  std::cout << "result: " << result << '\n';

  // example using std::enable_if_t to use it pre C++17 & 20
  auto result2 = sp::add_sametypes(5.4, 4.5, 20.);
  auto result3 = sp::add_sametypes(5, 4, 20);

  static_assert(std::is_same_v<decltype(result3), int>);
  static_assert(std::is_same_v<decltype(result2), double>);

  static_assert(std::is_same_v<decltype(result), double>);

  // uses concepts in implementation
  constexpr auto result4 = sp::add_sametypes2(1, 2, 3);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result4)>, int>);

  constexpr auto result5 = sp::add_sametypes2(1., 2.4, 3.);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result5)>, double>);

  constexpr auto result6 = sp::add_sametypes3(1.2, 2.4, 3.);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result6)>, double>);
  std::cout << "add_sametypes3: " << result6 << '\n';

  constexpr auto result7 = sp::add_sametypes4(1.2, 2.4, 3.);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result7)>, double>);

  constexpr auto result8 = sp::add_sametypes31<double>(1.2, 2.4, 3.);
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(result8)>, double>);

  // this does not work ??
  // constexpr auto result9 = sp::add_sametypes5(1.2, 2.4, 3.);

  std::puts("-------------> concepts test1 passed -------------<");
}
void concepts_test_stub() noexcept {
  std::puts("-------------> test stub -------------<");

  static_assert(not addable<int, double>);
  static_assert(not addable<double, float>);
  static_assert(addable<int, int>);
  static_assert(addable<float, float>);
  static_assert(not addable<NoAdd, ValidClass>);
  static_assert(not addable<NoAdd, NoAdd>);
  static_assert(addable<ValidClass, ValidClass>);
  static_assert(not addable<NotExcept, NotExcept>);
  static_assert(not addable<DifferentReturnType, DifferentReturnType>);

  std::puts("-------------> test stub passed -------------<");
}
void concepts_constexpr_functions() noexcept {
  std::puts("-------------> constexpr_functions -------------<");

  std::array<int, 1> a{};
  send_oneping(a);

  // size can not be determined in compile time
  std::vector myvec{1, 2, 3};
  // does not work since size of vec cannot be determined compiled time
  // send_oneping(myvec);
  std::puts("-------------> constexpr_functions passed -------------<");
}

void concepts_auto_variables() noexcept {
  std::puts("-------------> auto_variables -------------<");

  auto v1 = std::vector<int>{3, 4, 5};

  [[maybe_unused]] const auto v1_size = std::size(v1);

  [[maybe_unused]] const std::integral auto v1_size2 = v1.size();

  std::puts("-------------> auto_variables passed -------------<");
}

void concept_validate_data() noexcept {
  std::puts("-------------> validate_data -------------<");

  ComplexType cpt;
  send_data(cpt);
  static_assert(has_validation<ComplexType>);
  static_assert(not has_validation<SimpleType>);
  send_data(SimpleType{});

  std::puts("-------------> validate_data passed -------------<");
}

} // namespace sp
