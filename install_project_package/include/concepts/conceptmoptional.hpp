#pragma once
#include "messageExport.h"
#include <bit>
#include <concepts>
#include <cstddef>
#include <memory>
#include <optional>
#include <type_traits>
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
  T *as() { return std::bit_cast<T *>(new (std::addressof(data)) T()); }
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

// C++20 version; conditional copy constructor
template <typename T> struct moptional2 {
public:
  moptional2() = default;
  moptional2(const moptional2 &other)
    requires(std::is_copy_constructible_v<T>)
      : value{other.value} {}

private:
  storage_t<T> value{};
};
} // namespace sp
