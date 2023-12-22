#pragma once
#include "messageExport.h"

namespace sp {

template <typename T, typename G, typename... Bases>
struct promise_type_multibase : Bases... {
  T mvalue;

  // invoked by co_yield or co_return
  auto yield_value(T value) {
    mvalue = value;
    return std::suspend_always{};
  }

  G get_return_object() { return G{this}; }

  auto initial_suspend() noexcept { return std::suspend_always{}; }
  auto final_suspend() noexcept { return std::suspend_always{}; }

  void return_void() {}
  void unhandled_exception() { std::terminate(); }

  static auto get_return_object_on_allocation_failure() { return G{nullptr}; }
};

} // namespace sp
