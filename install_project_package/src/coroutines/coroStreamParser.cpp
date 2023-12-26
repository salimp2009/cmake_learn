#include "coroStreamParser.hpp"
#include <algorithm>
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

      if (ESC == b) {
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

void simulate_stream() {
  const std::vector<std::byte> fakeBytes1{0x70_B, ESC,   SOF,   ESC,   'H'_B,
                                          'e'_B,  'l'_B, 'l'_B, 'o'_B, ESC,
                                          SOF,    0x7_B, ESC,   SOF};

  // simulate stream
  auto stream1 = sender(std::move(fakeBytes1));

  auto p = parser();
  process_stream(stream1, p);

  const std::vector<std::byte> fakeBytes2{'W'_B, 'o'_B, 'r'_B, 'l'_B,
                                          'd'_B, ESC,   SOF,   0x99_B};

  auto stream2 = sender(std::move(fakeBytes2));
  process_stream(stream2, p);
}

} // namespace sp
