#include "coroDataStreamReader.hpp"
#include "coroStreamParser.hpp"

namespace sp {

FSM_v2 parser_v2(DataStreamReader &stream) {
  while (true) {
    std::byte b = co_await stream;
    if (ESC != b) {
      continue;
    }

    b = co_await stream;
    if (SOF != b) {
      continue;
    }
    std::string frame{};

    while (true) {
      b = co_await stream;

      if (ESC == b) {
        b = co_await stream;

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

void stream_simulator2() {
  std::vector<std::byte> fakeBytes1{0x70_B, ESC,   SOF,   ESC,   'H'_B,
                                    'e'_B,  'l'_B, 'l'_B, 'o'_B, ESC,
                                    SOF,    0x7_B, ESC,   SOF};

  auto stream1 = sender(std::move(fakeBytes1));

  DataStreamReader datareader{};
  auto p = parser_v2(datareader);

  for (const auto &b : stream1) {
    datareader.set(b);
    if (const auto &res = p(); res.length()) {
      handle_frame(res);
    }
  }
  std::vector<std::byte> fakeBytes2{'W'_B, 'o'_B, 'r'_B, 'l'_B,
                                    'd'_B, ESC,   SOF,   0x99_B};

  auto stream2 = sender(std::move(fakeBytes2));
  for (const auto &b : stream2) {
    datareader.set(b);
    if (const auto &res = p(); res.length()) {
      handle_frame(res);
    }
  }
}

} // namespace sp
