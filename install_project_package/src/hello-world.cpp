#include <Message.hpp>
#include <conceptbasics.hpp>
#include <cstdlib>
#include <numbers>

int main() {
  Message say_hello("Hello, CMake World!");

  std::cout << say_hello << '\n';

  Message say_goodbye("Goodbye, CMake World");
  std::cout << say_goodbye << '\n';
  static_assert(not sp::are_same_v<decltype(1), decltype(2.4)>);
  static_assert(not are_same2<decltype(1), decltype(2.4)>);

  Test2 tst2{};
  tst2.value2 = 7;
  // this will not compile since it is invisible in. Message.cpp
  // auto result2 = tst2.get_value2();

  // wont compile since it is not export using message_EXPORT
  // getUUID();

  // visibility check for concepts library; NOT Working
  sp::Test tst{};
  tst.value = 5;

  // this respects visibility since the definition of member function is in
  // conceptbasics.cpp tst.get_value();
  // sp::getnumber();

  auto result = sp::myadd(5.4, 5, 6.4, 100);
  std::cout << "result: " << result << '\n';

  // example using std::enable_if_t to use it pre C++17 & 20
  auto result2 = sp::add_sametypes(5.4, 4.5, 20.);
  auto result3 = sp::add_sametypes(5, 4, 20);

  static_assert(std::is_same_v<decltype(result3), int>);
  static_assert(std::is_same_v<decltype(result2), double>);

  static_assert(std::is_same_v<decltype(result), double>);
  // getUUID();
  return EXIT_SUCCESS;
}
