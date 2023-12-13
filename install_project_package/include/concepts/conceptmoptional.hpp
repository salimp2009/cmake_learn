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

// Concepts tp be used in optional2
template <typename T>
concept has_release = requires(T t) { t.release(); };

template <typename T>
concept NotTriviallyDestructible = not std::is_trivially_destructible_v<T>;

// C++20 version; conditional copy constructor
template <typename T> struct moptional2 {
public:
  moptional2() = default;

  moptional2(const moptional2 &other)
    requires(std::is_copy_constructible_v<T>)
      : value{other.value} {}

  ~moptional2()
    requires(NotTriviallyDestructible<T>)
  {
    if (has_value) {
      value.as()->~T();
    }

#ifdef DEBUG
    std::puts("not trivially destructible");
#endif // !#ifdef DEBUG
  }

  ~moptional2()
    requires(NotTriviallyDestructible<T> && has_release<T>)
  {
    if (has_value) {
      value.as()->release();
    }
#ifdef DEBUG
    std::puts("not trivially destructible & has_release");
#endif
  }

  ~moptional2()

    requires(has_release<T>)
  {
    if (has_value) {
      value.as()->release();
    }
#if DEBUG
    std::puts("has_release ");
#endif
  }

  ~moptional2() = default;

private:
  storage_t<T> value{};

  bool has_value{};
};

// not trivially destructible type
struct ComLike {
  ~ComLike() { release(); } // makes it not is_trivially_destructible_v
  void release() { std::puts("Releasing ComLike!"); }
  // std::string url{};
};

struct ComLikeNoRelease {
  ~ComLikeNoRelease() {} // makes it not is_trivially_destructible_v
  // std::string url{};
};

} // namespace sp
