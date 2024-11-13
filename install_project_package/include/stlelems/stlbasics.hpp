#pragma once

#include "messageExport.h"
#include <chrono>
#include <cstdint>

namespace sp {
message_EXPORT void stlchanges_basics1() noexcept;
message_EXPORT void time_zone_basics1() noexcept;
message_EXPORT void local_time_basics() noexcept;

union FloatOrInt {
  float f;
  uint32_t i;
};

message_EXPORT void print_zone_time(std::chrono::sys_days sysdays,
                                    std::string_view zone);

} // namespace sp
