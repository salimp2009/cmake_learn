#pragma once

#include "fmt/core.h"
#include "messageExport.h"
#include <chrono>
#include <cstdint>
#include <print>

namespace sp {
message_EXPORT void stlchanges_basics1() noexcept;
message_EXPORT void time_zone_basics1() noexcept;
message_EXPORT void local_time_basics() noexcept;

union FloatOrInt {
  float f;
  uint32_t i;
};

/* message_EXPORT */ void print_zone_time(std::chrono::sys_days sysdays,
                                          std::string_view zone);

message_EXPORT constexpr inline void test(int n) { n += 1; }

struct message_EXPORT Vector {
  int X;
  int Y;
  template <typename Self> void Print(this Self &&self) {
    std::println("Vector from stlbasics; (x:{}, y:{})", self.X, self.Y);
  }
};

template <typename T> inline constexpr message_EXPORT void testextern() {
  fmt::println("testextern templ {}", "maintemplate");
}
extern template message_EXPORT void testextern<float>();

} // namespace sp
