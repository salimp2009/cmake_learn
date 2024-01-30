#pragma once

#include "messageExport.h"
#include <cstddef>

namespace sp {

message_EXPORT void nttp_basics1() noexcept;

template <typename T, std::size_t N> struct message_EXPORT Array {
  T data[N];
};

template <double N> struct message_EXPORT Doubles {};
} // namespace sp
