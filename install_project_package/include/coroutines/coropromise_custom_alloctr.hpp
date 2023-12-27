#pragma once
#include "corobase.hpp"
#include <cstddef>

namespace sp {

struct arena {
  void *allocate(std::size_t size) noexcept;
  void deallocate(void *ptr, std::size_t) noexcept;

  static arena *getfrom_ptr(void *ptr, std::size_t size);
};

template <typename T, typename G, bool InitialSuspnd = true>
struct promise_custom_alloc_base
    : public promise_type_base<T, G, InitialSuspnd> {

  using promise_type_base<T, G, InitialSuspnd>::promise_type_base;

  template <typename... TheRest>
  void *operator new(std::size_t size, arena &a, TheRest &&...) noexcept {

    return a.allocate(size);
  }

  void operator delete(void *ptr, std::size_t size) {
    arena::getfrom_ptr(ptr, size)->deallocate(ptr, size);
  }
};

} // namespace sp
