#pragma once
#include "coroDataStreamReader.hpp"
#include "corobase.hpp"
#include "messageExport.h"
#include <cstddef>
#include <vector>

namespace sp {

struct arena {
  void *allocate(std::size_t size) noexcept;
  void deallocate(void *ptr, std::size_t) noexcept;

  static arena *getfrom_ptr(void *ptr, std::size_t size);
};

template <typename T, typename G, bool InitialSuspnd = true>
struct promise_custom_alloc_base {
  T mvalue;

  // invoked by co_yield or co_return
  auto yield_value(T value) {
    mvalue = value;
    return std::suspend_always{};
  }

  G get_return_object() { return G{this}; }

  auto initial_suspend() noexcept {
    if constexpr (InitialSuspnd) {
      return std::suspend_always{};
    } else {
      return std::suspend_never{};
    }
  }

  auto final_suspend() noexcept { return std::suspend_always{}; }

  void return_void() {}
  void unhandled_exception() { std::terminate(); }

  static auto get_return_object_on_allocation_failure() { return G{nullptr}; }

  template <typename... TheRest>
  void *operator new(std::size_t size, arena &a, TheRest &&...) noexcept {

    return a.allocate(size);
  }

  void operator delete(void *ptr, std::size_t size) {
    arena::getfrom_ptr(ptr, size)->deallocate(ptr, size);
  }
};

template <typename T, bool InitialSuspnd = true>
struct message_EXPORT generator_cust_alloc {
  using promise_type =
      promise_custom_alloc_base<T, generator_cust_alloc, InitialSuspnd>;

  using promise_type_handle = std::coroutine_handle<promise_type>;

  using iterator = detail::iterator<promise_type>;

  iterator begin() { return {m_corohdl}; }
  iterator end() { return {}; }

  // generator is move only since we need to manage the memory resource
  // because compiler does not know when coroutine is not anymore needed
  generator_cust_alloc(const generator_cust_alloc &) = delete;
  generator_cust_alloc(generator_cust_alloc &&rhs)
      : m_corohdl(std::exchange(rhs.m_corohdl, nullptr)) {}

  ~generator_cust_alloc() {
    if (m_corohdl) {
      m_corohdl.destroy();
    }
  }

  T operator()() {
    T tmp{};
    std::swap(tmp, m_corohdl.promise().mvalue);
    return tmp;
  }

private:
  // the default constructor is private
  // therefore promise has to be friend
  friend promise_type;

  explicit generator_cust_alloc(promise_type *p)
      : m_corohdl(promise_type_handle::from_promise(*p)) {}

  // coroutine handle
  promise_type_handle m_corohdl;
};

using FSM_v3 = generator_cust_alloc<std::string, false>;

message_EXPORT FSM_v3 parser_v3(arena &, DataStreamReader &stream);

message_EXPORT generator_cust_alloc<std::byte>
sender(arena &a, std::vector<std::byte> fakeBytes);

message_EXPORT void stream_simulator_arena_alloc();

} // namespace sp
