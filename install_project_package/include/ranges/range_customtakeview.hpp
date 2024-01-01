#pragma once

#include <iterator>
#include <ranges>
#include <type_traits>
#include <vector>

namespace sp {

template <std::ranges::view R>
class custom_take_view
    : public std::ranges::view_interface<custom_take_view<R>> {
private:
  R mbase{};
  std::ranges::range_difference_t<R> mcount{};

public:
  custom_take_view()
    requires(std::is_default_constructible_v<R>)
  = default;

  constexpr custom_take_view(R bs, std::ranges::range_difference_t<R> cnt)
      : mbase{std::move(bs)}, mcount{cnt} {}

  // view_interface members
  constexpr R base() const & { return mbase; }
  constexpr R base() && { return std::move(mbase); }

  constexpr auto begin() { return std::ranges::begin(mbase); }
  constexpr auto end() { return std::ranges::next(std::begin(mbase), mcount); }
};

} // namespace sp
