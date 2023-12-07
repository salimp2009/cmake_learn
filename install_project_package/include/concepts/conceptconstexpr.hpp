#pragma once

#include <cstddef>
#include <cstdio>
#include <messageExport.h>

namespace sp {
constexpr auto getsize(const std::ranges::range auto &t = {}) {
  return t.size();
};

template <typename T, std::size_t N>
concept size_check = (getsize<T>() == N);

constexpr auto send_oneping(size_check<1> auto &cont) {
  std::puts("returning one ping");
  return cont.size();
};

} // namespace sp
