#include "coroStreamParser.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <vector>

namespace sp {

FSM parser() {
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

generator<std::byte> sender(std::vector<std::byte> fakeBytes) {
  for (const auto &b : fakeBytes) {
    co_yield b;
  }
}
void handle_frame(std::string_view stream_result) {
  fmt::println("result from stream: {}", stream_result);
}

void process_stream(generator<std::byte> &stream, FSM &parse) {
  for (const auto &b : stream) {
    // send new byte to parse coroutine
    parse.send_signal(b);
  }
  if (const auto &res = parse(); res.length()) {
    handle_frame(res);
  }
}

} // namespace sp
