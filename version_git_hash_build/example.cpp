#include "version.hpp"
#include <iostream>

int main() {
  std::cout << "This is output from code v" << PROGRAM_VERSION << '\n';
  std::cout << "This program is generated from: " << GIT_HASH << '\n';
  std::cout << "This program is generated from: " << GIT_STATUS << '\n';
  std::cout << "Hello CMake world!" << '\n';
}
