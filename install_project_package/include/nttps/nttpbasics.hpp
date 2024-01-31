#pragma once

#include "messageExport.h"
#include <cstddef>

namespace sp {

// test functions linked to main
message_EXPORT void nttp_basics1() noexcept;
message_EXPORT void safe_printf() noexcept;

template <typename T, std::size_t N> struct message_EXPORT Array {
  T data[N];
};

template <double N> struct message_EXPORT Doubles {};
} // namespace sp
