#pragma once
#include "messageExport.h"
#include <type_traits>

template <typename T, typename... Ts>

message_EXPORT constexpr inline bool are_same =
    std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename... T1,
          typename U = std::common_type<T, T1...>::type>
U myfunct(U myval) {
  return myval;
}

struct message_NO_EXPORT Test {
  int value{};
};
