#include <Message.hpp>
#include <conceptbasics.hpp>
#include <cstdlib>

int main() {
  Message say_hello("Hello, CMake World!");

  std::cout << say_hello << '\n';

  Message say_goodbye("Goodbye, CMake World");
  std::cout << say_goodbye << '\n';
  static_assert(not are_same<decltype(1), decltype(2.4)>);
  static_assert(not are_same2<decltype(1), decltype(2.4)>);

  Test2 tst2{};
  tst2.value2 = 7;
  // this will not compile since it is invisible in. Message.cpp
  // auto result2 = tst2.get_value2();

  // wont compile since it is not export using message_EXPORT
  // getUUID();

  // visibility check for concepts library; NOT Working
  Test tst{};
  tst.value = 5;
  // this respects visibility since it is in conceptbasics.cpp
  // tst.get_value();

  // this respects visibility since the definition is in conceptbasics.cpp
  // getnumber();

  auto result = myfunct(5.4, 5, 6.4);
  static_assert(std::is_same_v<decltype(result), double>);
  // getUUID();
  return EXIT_SUCCESS;
}
