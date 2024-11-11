#pragma once

#include "messageExport.h"
#include <cstdint>

namespace sp {
message_EXPORT void stlchanges_basics1() noexcept;
message_EXPORT void time_zone_basics1() noexcept;

union FloatOrInt {
  float f;
  uint32_t i;
};
} // namespace sp
