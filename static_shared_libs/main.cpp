#include "message.hpp"
#include <cstdlib>
#include <iostream>

int main() {
  Message msg("Hello cmake");
  std::cout << msg << '\n';
  return 0;
}
