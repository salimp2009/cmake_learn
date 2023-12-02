#pragma once
#include "messageExport.h"
#include <type_traits>

template <typename T, typename... Ts>
constexpr inline bool are_same = std::conjunction_v<std::is_same<T, Ts>...>;

template <typename T, typename... T1,
          typename U = std::common_type<T, T1...>::type>
message_NO_EXPORT U myfunct(T first, T1... myval) {
  return first;
}

struct Test {
  int value{};
  int get_value() const;
};

int getnumber();
