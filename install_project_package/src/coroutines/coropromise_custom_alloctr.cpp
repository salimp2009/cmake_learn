#include "coropromise_custom_alloctr.hpp"
#include "coroDataStreamReader.hpp"
#include "coroStreamParser.hpp"

namespace sp {

void *arena::allocate(std::size_t size) noexcept {
  auto objectsize = size;
  size += sizeof(arena *);

  char *ptr = new char[size];
  [[maybe_unused]] arena *aa = reinterpret_cast<arena *>(ptr + objectsize);
  aa = this;

  arena *b = reinterpret_cast<arena *>(ptr + objectsize);

#ifdef DEBUG
  printf("custom alloc %zu  %s  %p  %p\n", objectsize, ptr, this, b);
#endif

  return ptr;
}

void arena::deallocate(void *ptr, std::size_t size) noexcept {

#ifdef DEBUG
  printf("custom dealloc %zu  %p  %p\n", size, ptr, this);
#endif

  delete[] static_cast<char *>(ptr);
}

arena *arena::getfrom_ptr(void *ptr, std::size_t size) {
  return reinterpret_cast<arena *>(static_cast<char *>(ptr) + size);
}

FSM_v3 parser_v3(arena &, DataStreamReader &stream) {
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

generator_cust_alloc<std::byte> sender(arena &a,
                                       std::vector<std::byte> fakeBytes) {
  for (const auto &b : fakeBytes) {
    co_yield b;
  }
}

void stream_simulator_arena_alloc() {
  arena arena_alloc1{};
  arena arena_alloc2{};
  std::vector<std::byte> fakeBytes1{0x70_B, ESC,   SOF,   ESC,   'H'_B,
                                    'e'_B,  'l'_B, 'l'_B, 'o'_B, ESC,
                                    SOF,    0x7_B, ESC,   SOF};

  auto stream1 = sender(arena_alloc1, std::move(fakeBytes1));
  DataStreamReader dr{};

  auto p = parser_v3(arena_alloc2, dr);

  for (const auto &b : stream1) {
    dr.set(b);
  }

  if (const auto res = p(); res.length()) {
    handle_frame(res);
  }

  std::vector<std::byte> fakeBytes2{'W'_B, 'o'_B, 'r'_B, 'l'_B,
                                    'd'_B, ESC,   SOF,   0x99_B};
  auto stream2 = sender(arena_alloc1, std::move(fakeBytes2));

  for (const auto &b : stream2) {
    dr.set(b);
  }

  if (const auto res = p(); res.length()) {
    handle_frame(res);
  }
}

} // namespace sp
