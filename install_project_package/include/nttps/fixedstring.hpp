#pragma once

#include "messageExport.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <type_traits>

namespace sp {

template <typename CharT, std::size_t N> struct message_EXPORT fixed_string {
  alignas(char) CharT data[N]{};

  constexpr fixed_string(const CharT (&str)[N]) { std::copy_n(str, N, data); }
};

template <fixed_string Str> struct message_EXPORT fixed_string_container {

  constexpr void print() { fmt::println("{}", Str.data); }
};

template <fixed_string str> struct message_EXPORT format_string {
  static constexpr auto fmt = str;
  static constexpr auto num_args = std::ranges::count(fmt.data, '%');

  // implicit conversion operator; also know cast operator
  // https://en.cppreference.com/w/cpp/language/cast_operator
  operator const auto *() const { return fmt.data; }
};

template <fixed_string str> constexpr auto operator""_fs() {
  return format_string<str>{};
}

template <typename T, typename U>
constexpr bool plain_same_v =
    std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

template <typename T> constexpr static bool match(const char c) {
  switch (c) {
  case 'd':
    return plain_same_v<int, T>;
  case 'c':
    return plain_same_v<char, T>;
  case 'f':
    return plain_same_v<double, T>;
  case 's':
    return (plain_same_v<char, std::remove_all_extents_t<T>> and
            std::is_array_v<T>) or
           (plain_same_v<char *, std::remove_all_extents_t<T>> and
            std::is_pointer_v<T>);
  case 'p':
    return plain_same_v<void *, std::remove_all_extents_t<T>> &&
           std::is_pointer_v<T>;
  }
  return false;
}

void print(auto fmt, const auto &...args) {
  static_assert(fmt.num_args == sizeof...(args));
  std::printf(fmt, args...);
}

} // namespace sp
