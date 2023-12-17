#pragma once

#include "messageExport.h"
#include <coroutine>
#include <iterator>
#include <utility>

namespace sp {

namespace detail {

template <typename PromiseType> struct iterator {
  std::coroutine_handle<PromiseType> m_corohdl{nullptr};
};

} // namespace detail

template <typename T, typename G> struct promise_type_base {};

template <typename T> struct generator {
  using promise_type = promise_type_base<T, generator>;
  using promise_type_handle = std::coroutine_handle<promise_type>;

  using iterator = detail::iterator<promise_type>;

  iterator begin() { return {m_corohdl}; }
  iterator end() { return {}; }

  // generator is move only since we need to manage the memory resource
  // because compiler does not know when coroutine is not anymore needed
  generator(const generator &) = delete;
  generator(generator &&rhs)
      : m_corohdl(std::exchange(rhs.m_corohdl, nullptr)) {}

  ~generator() {
    if (m_corohdl) {
      m_corohdl.destroy();
    }
  }

private:
  // the default constructor is private
  // therefore promise has to be friend
  friend promise_type;

  explicit generator(promise_type *p)
      : m_corohdl(promise_type_handle::from_promise(*p)) {}

  // coroutine handle
  promise_type_handle m_corohdl;
};

} // namespace sp
