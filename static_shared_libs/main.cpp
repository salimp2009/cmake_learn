#include "message.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>

int main() {
  Message msg("Hello cmake");
  const auto sptr = std::make_shared<int>(5);
  auto sptr2 = sptr;
  std::cout << msg << " ptr: " << *sptr << ", ptr2: " << *sptr2 << '\n';
  return 0;
}
