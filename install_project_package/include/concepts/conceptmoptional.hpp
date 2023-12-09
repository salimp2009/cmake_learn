#pragma once
#include "messageExport.h"
#include <bit>
#include <cstddef>
#include <optional>
#include <type_traits>
namespace sp {

template <std::size_t Len, std::size_t Align> struct aligned_storage {
  struct type {
    alignas(Align) unsigned char data[Len];
  };
};

template <std::size_t Len, std::size_t Align>
using aligned_storage_t = aligned_storage<Len, Align>::type;

template <typename T> union storage_t {
  using m_aligned_storage_t = aligned_storage_t<sizeof(T), alignof(T)>;
  m_aligned_storage_t data;

  storage_t() = default;

  // T *as() { std::construct_at(std::bit_cast<T *>(data), T()); }
  T *as() { return std::bit_cast<T *>(new (&data) T()); }
};

template <typename T> class message_EXPORT moptional {
public:
  moptional() = default;

  template <typename U,
            typename = std::enable_if_t<std::is_same_v<U, moptional> &&
                                        std::is_copy_constructible_v<T>>>
  moptional(const U &other) : value{other.value} {}

private:
  storage_t<T> value;
};

constexpr inline std::optional<int> myval{1};

} // namespace sp
