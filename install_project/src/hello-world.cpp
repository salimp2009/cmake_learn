#include "Message.hpp"
#include <cstdlib>

int main() {
  Message say_hello("Hello, CMake World!");

  std::cout << say_hello << '\n';

  Message say_goodbye("Goodbye, CMake World");

  std::cout << say_goodbye << '\n';

  return EXIT_SUCCESS;
}
