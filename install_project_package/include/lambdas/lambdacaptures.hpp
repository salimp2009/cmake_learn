#pragma once

#include "messageExport.h"
#include <climits>

namespace sp {

class message_EXPORT SomeCaptures {
private:
  int val = 3;

public:
  constexpr int double_val() const {
    // [this] captures members by reference, [*this] captures by value
    // [=] captures local variable in function by value
    // but class members by refence in C++17 implicitly, depreciated in C++20
    // [=, this] captures local vars by value, class members by reference
    // [=i *this] captures locals by value, class membrs by reference
    auto doubling = [*this] {
      assert(val * 2 <= INT_MAX);
      return val * 2;
    };
    return doubling();
  };
};
} // namespace sp
