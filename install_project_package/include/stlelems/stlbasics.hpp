#pragma once

#include "messageExport.h"

namespace sp {
message_EXPORT void stlchanges_basics1() noexcept;

union FloatOrInt {
  float f;
  uint32_t i;
};

} // namespace sp
