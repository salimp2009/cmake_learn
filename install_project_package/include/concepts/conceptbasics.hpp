#pragma once
#include "messageExport.h"
#include <type_traits>

namespace sp message_NO_EXPORT {
template <typename T, typename... T1,
          typename U = std::common_type<T, T1...>::type>
message_NO_EXPORT U myadd(T first, T1... myval) {
  return ((first + myval) + ...);
}

struct Test {
  int value{};
  int get_value() const;
};

template <typename T, typename... Ts>
constexpr inline bool message_NO_EXPORT are_same_v =
    std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename...> struct first_arg {
  using type = T;
};

template <typename... Args> using first_arg_t = first_arg<Args...>::type;

template <typename... Args, typename R = std::enable_if_t<are_same_v<Args...>,
                                                          first_arg_t<Args...>>>
R add_sametypes(Args... args) noexcept {
  return (... + args);
}

int getnumber();

} // namespace sp message_NO_EXPORT
