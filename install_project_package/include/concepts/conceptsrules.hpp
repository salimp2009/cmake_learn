#pragma once
#include <cstdio>
#include <type_traits>
namespace sp {

template <typename T, typename U>
concept IsSameHelper = std::is_same_v<T, U>;

template <typename T, typename W>
concept IsSame = IsSameHelper<T, W> && IsSameHelper<W, T>;

template <typename T>
concept AlwaysTrue = std::true_type::value;

template <typename T, typename U>
  requires IsSame<U, T>
inline constexpr auto add(const T &t, const U &u) {
  puts("least constrained add function");
  return t + u;
}

template <typename T, typename U>
  requires IsSame<T, U> && AlwaysTrue<T>
inline constexpr auto add(const T &t, const U &u) {
  puts("most constrained add function");
  return t + u;
}

} // namespace sp
