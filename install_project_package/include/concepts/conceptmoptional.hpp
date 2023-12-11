#pragma once
#include "messageExport.h"
#include <bit>
#include <concepts>
#include <cstddef>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
namespace sp {

struct Empty {};

template <std::size_t Len, std::size_t Align = alignof(Empty)>
struct aligned_storage {
  struct type {
    alignas(Align) unsigned char data[Len];
  };
};

template <std::size_t Len, std::size_t Align>
using aligned_storage_t = aligned_storage<Len, Align>::type;

template <typename T> union storage_t {
  using m_aligned_storage_t = aligned_storage_t<sizeof(T), alignof(T)>;
  m_aligned_storage_t data;

  constexpr storage_t() = default;

  // T *as() { std::construct_at(std::bit_cast<T *>(data), T()); }
  [[nodiscard("returned pointer not used!!")]] T *as() {
    return std::bit_cast<T *>(new (std::addressof(data)) T());
  }
};

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

template <typename T> class message_EXPORT moptional {
public:
  constexpr moptional() = default;

  // this does not work since the copy constructor cannot be templated
  template <typename U,
            typename = std::enable_if_t<std::is_same_v<U, moptional> &&
                                        std::is_copy_constructible_v<T>>>
  constexpr moptional(const U &other) : value{other.value} {}

private:
  storage_t<T> value{};
};

struct NotCopyable {
  NotCopyable(const NotCopyable &) = delete;
  NotCopyable &operator=(const NotCopyable &) = delete;
};

struct copyable {};
struct notCopyable {
  notCopyable() = default;
  notCopyable(const notCopyable &) = delete;
  notCopyable &operator=(const notCopyable &) = delete;
};

// pre C++20 to create a deleted copy constructor
// to derived from a base type that has copy constructor deleted
template <typename T>
struct moptional1 : public std::conditional_t<std::is_copy_constructible_v<T>,
                                              copyable, notCopyable> {
public:
  moptional1() = default;

private:
  storage_t<T> value{};
};

// C++20 version; conditional copy constructor
template <typename T> struct moptional2 {
public:
  moptional2() = default;

  moptional2(const moptional2 &other)
    requires(std::is_copy_constructible_v<T>)
      : value{other.value} {}

  ~moptional2()
    requires(not std::is_trivially_destructible_v<T>)
  {
    if (has_value) {
      value.as()->T();
    }
  }

  ~moptional2() = default;

private:
  storage_t<T> value{};

  bool has_value{};
};

} // namespace sp
