#include "coroStreamParser.hpp"

namespace sp {

FSM parse() {
  while (true) {
    std::byte b = co_await std::byte{};
    if (ESC != b) {
      continue;
    }

    b = co_await std::byte{};
    if (SOF != b) {
      continue;
    }
    std::string frame{};
    while (true) {
      b = co_await std::byte{};

      if (ESC != b) {
        b = co_await std::byte{};
        if (SOF == b) {
          co_yield frame;
          break;
        } else if (ESC != b) {
          break;
        }
      }

      frame += static_cast<char>(b);
    }
  }
}

} // namespace sp
