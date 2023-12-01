#include <Message.hpp>
#include <conceptbasics.hpp>
#include <cstdlib>

int main() {
  Message say_hello("Hello, CMake World!");

  std::cout << say_hello << '\n';

  Message say_goodbye("Goodbye, CMake World");
  std::cout << say_goodbye << '\n';
  static_assert(not are_same<decltype(1), decltype(2.4)>);

  // wont compile since it is not export using message_EXPORT
  // getUUID();
  Test tst;
  tst.value = 5;
  auto result = myfunct<int>(5.4);
  // getUUID();
  return EXIT_SUCCESS;
}
