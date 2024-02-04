#pragma once

#include "messageExport.h"
#include <algorithm>
#include <array>
// #include <concepts>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <span>
#include <type_traits>
#include <utility>

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
  char temp_prefix = ' ';

  switch (c) {
  case 'd':
    return plain_same_v<int, T>;
  case 'c':
    return plain_same_v<char, T>;
  case 'f':
    return plain_same_v<double, T> || std::is_floating_point_v<T>;
  case 's':
    return (plain_same_v<char, std::remove_all_extents_t<T>> and
            std::is_array_v<T>) or
           (plain_same_v<char *, std::remove_all_extents_t<T>> and
            std::is_pointer_v<T>);
  case '#':
    temp_prefix = '#';
    [[fallthrough]];
  // static_assert(not plain_same_v<double, T>, "expected int");
  case 'X':
  case 'x':
    return (
        plain_same_v<unsigned short, T> || plain_same_v<std::size_t, T> ||
        plain_same_v<unsigned long long, T> || plain_same_v<unsigned int, T> ||
        plain_same_v<
            int,
            T>)&&(not plain_same_v<double,
                                   T>)&&(not(plain_same_v<char,
                                                          std::
                                                              remove_all_extents_t<
                                                                  T>> and
                                             std::is_array_v<T> &&
                                             not std::floating_point<T>) ||
                                         not(plain_same_v<
                                                 char *,
                                                 std::remove_all_extents_t<
                                                     T>> &&
                                             std::is_pointer_v<T>));
  case 'a':
    return (not plain_same_v<int, T>)&&((temp_prefix != '#')) &&
           (std::is_floating_point_v<T> || plain_same_v<long double, T> ||
            plain_same_v<
                double,
                T>)&&(not(plain_same_v<char, std::remove_all_extents_t<T>> and
                          std::is_array_v<T>) ||
                      not(plain_same_v<char *, std::remove_all_extents_t<T>> &&
                          std::is_pointer_v<T>));

  case 'p':
    return plain_same_v<void *, std::remove_all_extents_t<T>> &&
           std::is_pointer_v<T>;
  }
  return false;
}

// helper to search the specifier with the given index
template <int I, typename CharT>
constexpr auto get(const std::span<const CharT> &str) {
  auto start = std::begin(str);
  const auto end = std::end(str);

  for (int i = 0; i <= I; i++) {
    start = std::ranges::find(start, end, '%');
    ++start;
    if (*start == '#')
      ++start;
  }

  // returns the format specifier at the given index
  return *start;
}

template <typename CharT, typename... Ts>
constexpr bool is_matching(std::span<const CharT> str) {
  return [&]<std::size_t... I>(std::index_sequence<I...>) {
    return ((match<Ts>(get<I>(str))) && ...);
  }(std::make_index_sequence<sizeof...(Ts)>{});
}

template <typename... Args> void print(auto fmt, const Args &...args) {
  static_assert(fmt.num_args == sizeof...(args),
                "number of values dont match specifiers!");
  static_assert(is_matching<std::decay_t<decltype(fmt.fmt.data[0])>, Args...>(
                    fmt.fmt.data),
                "type of values dont match the specifiers");

  std::printf(fmt, args...);
}

} // namespace sp
