#pragma once

namespace sp {

namespace detail {

template <typename T, bool = std::is_trivially_destructible_v<T>>
struct opt_storage_base {
  constexpr opt_storage_base() noexcept : m_empty{}, m_has_value{false} {}

  template <typename... U>
  constexpr opt_storage_base(std::in_place_t, U &&...args) noexcept
      : m_value{std::forward<U>(args)...}, m_has_value{true} {}

  ~opt_storage_base()
    requires(not std::is_trivially_destructible_v<T>)
  {
    if (m_has_value) {
      m_value.~T();
      m_has_value = false;
    }
  }

  struct empty {};
  union {
    empty m_empty{};
    T m_value;
  };
  bool m_has_value{};
};

template <typename T> struct opt_operations_base : opt_storage_base<T> {
  using opt_storage_base<T>::opt_storage_base;

  void hard_reset() noexcept { get().~T(); }

  template <typename... Args> void construct(Args... args) {
    // if C++20
    std::construct_at(std::addressof(this->m_value), args...);
    // if not C++20
    // ::new (std::addressof(this->value)) T(std::forward<Args>(args)...);
  }

  bool has_value() const { return this->m_has_value; }

  constexpr T &get() & { return this->m_value; }
  constexpr const T &get() const & { return this->m_value; }
  constexpr T &&get() && { return std::move(this->m_value); }
};

} // end of namespace detail

} // namespace sp
