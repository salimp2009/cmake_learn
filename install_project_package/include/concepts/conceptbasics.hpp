#pragma once
#include "messageExport.h"
#include <type_traits>

namespace sp message_NO_EXPORT {
// concepts tests
message_EXPORT void concepts_test1() noexcept;

struct Test {
  int value{};
  int get_value() const;
};

int getnumber();

template <typename T, typename... T1,
          typename U = std::common_type<T, T1...>::type>
message_NO_EXPORT U myadd(T first, T1... myval) {
  return ((first + myval) + ...);
}

// pre C++20 concepts
template <typename T, typename... Ts>
constexpr inline bool message_NO_EXPORT are_same_v =
    std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename...> struct first_arg {
  using type = T;
};

template <typename... Args> using first_arg_t = first_arg<Args...>::type;

template <typename... Args, typename R = std::enable_if_t<are_same_v<Args...>,
                                                          first_arg_t<Args...>>>
constexpr R add_sametypes(Args &&...args) noexcept {
  return (... + args);
}

// C++20 Concepts
template <typename... Args>
  requires are_same_v<Args...>
constexpr auto add_sametypes2(Args &&...args) {
  return (... + args);
}

template <typename T, typename U>
concept are_same = std::is_same_v<T, U> && std::is_same_v<U, T>;

} // namespace sp message_NO_EXPORT
