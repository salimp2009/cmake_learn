#pragma once

#include <concepts>
#include <type_traits>
#include <utility>
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

  opt_operations_base() = default;

  opt_operations_base(const opt_operations_base &rhs)
    requires(not std::is_trivially_copy_constructible_v<T>)
      : opt_storage_base<T>() {
    if (rhs.has_value()) {
      this->construct(rhs.get());
    } else {
      this->m_has_value = false;
    }
  }

  opt_operations_base(opt_operations_base &&rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
    requires(not std::is_trivially_move_constructible_v<T>)
  {
    if (rhs.has_value()) {
      this->construct(std::move(rhs.get()));
    } else {
      this->m_has_value = false;
    }
  }

  opt_operations_base &operator=(const opt_operations_base &rhs)
    requires(not std::is_trivially_copy_assignable_v<T>)
  {
    this->assign(rhs);
    return *this;
  }

  opt_operations_base &operator=(const opt_operations_base &&rhs) noexcept(
      std::is_nothrow_move_constructible_v<T> &&
      std::is_nothrow_move_assignable_v<T>)
    requires(not std::is_trivially_move_assignable_v<T>)
  {
    this->assign(std::move(rhs));
    return *this;
  }
  opt_operations_base(const opt_operations_base &rhs) = default;
  opt_operations_base(opt_operations_base &&rhs) noexcept = default;
  opt_operations_base &operator=(const opt_operations_base &) = default;
  opt_operations_base &operator=(const opt_operations_base &&) = default;
  ~opt_operations_base() = default;

  void hard_reset() noexcept {
    this->get().~T();
    this->m_has_value = false;
  }

  template <class Opt> void assign(Opt &rhs) {
    if (this->has_value()) {
      if (rhs.has_value()) {
        this->m_value = std::forward<Opt>(rhs.get());
      } else {
        this->m_value.~T();
        this->m_has_value = false;
      }

    } else if (rhs.has_value()) {
      construct(std::forward<Opt>(rhs.get()));
    }
  }

  template <typename... Args>
  void construct(Args... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>) {
    // if C++20
    std::construct_at(std::addressof(this->m_value),
                      std::forward<Args>(args)...);
    // if not C++20
    // ::new (std::addressof(this->value)) T(std::forward<Args>(args)...);

    this->m_has_value = true;
  }

  bool has_value() const { return this->m_has_value; }

  constexpr T &get() & { return this->m_value; }
  constexpr const T &get() const & { return this->m_value; }
  constexpr T &&get() && noexcept { return std::move(this->m_value); }
};

} // end of namespace detail

} // namespace sp
