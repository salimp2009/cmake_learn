#pragma once

#include "messageExport.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace sp {

template <typename CharT, std::size_t N> struct message_EXPORT fixed_string {
  alignas(char) CharT data[N]{};

  constexpr fixed_string(const CharT (&str)[N]) { std::copy_n(str, N, data); }
};

template <fixed_string Str> struct message_EXPORT fixed_string_container {

  void print() { fmt::println("{}", Str.data); }
};

} // namespace sp
