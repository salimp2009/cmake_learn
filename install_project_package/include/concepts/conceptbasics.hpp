#pragma once
// #include "conceptbasics_check.hpp"
#include "messageExport.h"
#include <concepts>
#include <spanstream>
#include <type_traits>

namespace sp message_NO_EXPORT {
// concepts tests
// message_EXPORT void concepts_test1() noexcept;

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

// helper type traits
template <typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<
    std::is_same<std::remove_cvref_t<T>, std::remove_cvref_t<Ts>>...>;

template <typename T, typename...> struct first_arg {
  using type = T;
};

template <typename... Args> using first_arg_t = first_arg<Args...>::type;

// pre C++20 concepts
template <typename... Args, typename R = std::enable_if_t<are_same_v<Args...>,
                                                          first_arg_t<Args...>>>
constexpr R add_sametypes(Args &&...args) noexcept {
  return (... + args);
}

// C++20 Concepts
template <typename... Args>
  requires are_same_v<Args...>
constexpr auto add_sametypes2(Args &&...args) noexcept {
  return (... + args);
}

template <typename T, typename... Args>
concept are_same = ((std::is_same_v<T, Args> && std::is_same_v<T, Args>)&&...);

template <typename T, typename... Args>
  requires are_same<T, Args...>
constexpr auto add_sametypes3(T val, Args &&...args) noexcept {
  return (val + ... + args);
}

template <typename T, typename... Args>
// requires are_same<T, Args...>
constexpr auto add_sametypes31(are_same<T> auto &&...args) noexcept {
  return (... + args);
}

template <typename... Args>
concept addable = requires(Args... args) {
  (... + args);
  requires are_same_v<Args...>;
  requires(sizeof...(Args) > 1);
  { (... + args) } noexcept -> std::same_as<first_arg_t<Args...>>;
};

template <typename... Args>
  requires addable<Args...>
constexpr inline auto add_sametypes4(Args... args) noexcept {
  return (... + args);
}

// this does not work
constexpr inline auto add_sametypes5(addable auto &&...args) noexcept {
  return (... + args);
}

} // namespace sp message_NO_EXPORT
