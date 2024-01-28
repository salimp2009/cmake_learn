#pragma once

#include "messageExport.h"

namespace sp {

message_EXPORT void aggregate_basics1() noexcept;

struct message_EXPORT Point2D {
  int x{};
  int y{};
};

struct message_EXPORT Point3D {
  int x{};
  int y{};
  int z{};
};

struct message_EXPORT LifetimeExtension {
  int &&rval;
};

struct message_EXPORT NotDefaultConstructible {
  int x;

private:
  NotDefaultConstructible() = delete;
};

} // namespace sp
