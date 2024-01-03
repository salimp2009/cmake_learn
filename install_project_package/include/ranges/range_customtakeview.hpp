#pragma once

#include "messageExport.h"
#include <algorithm>
#include <iterator>
#include <ranges>

namespace sp {

template <std::ranges::view R>
class custom_take_view
    : public std::ranges::view_interface<custom_take_view<R>> {
private:
  R mbase{};
  std::ranges::range_difference_t<R> mcount{};

public:
  custom_take_view()
    requires(std::default_initializable<R>)
  = default;

  constexpr custom_take_view(R base, std::ranges::range_difference_t<R> count)
      : mbase{std::move(base)}, mcount{count} {}

  // view_interface members
  constexpr R base() const & { return mbase; }
  constexpr R base() && { return std::move(mbase); }

  constexpr auto begin() { return std::ranges::begin(mbase); }
  constexpr auto end() {
    auto newend = std::min<std::ranges::range_difference_t<R>>(
        std::ranges::distance(mbase), mcount);
    return std::ranges::next(std::begin(mbase), newend);
  }
};

// Deduction guide
template <std::ranges::range R>
custom_take_view(R &&base, std::ranges::range_difference_t<R>)
    -> custom_take_view<std::ranges::views::all_t<R>>;

namespace message_NO_EXPORT details {
template <typename T>
concept iter_diff_type = requires { std::iter_difference_t<T>(); };

template <iter_diff_type T> struct custom_take_range_adaptor_closure {
  T mcount;
  constexpr explicit custom_take_range_adaptor_closure(T count)
      : mcount{count} {}

  template <std::ranges::viewable_range R>
  constexpr auto operator()(R &&r) const {
    return custom_take_view(std::forward<R>(r), mcount);
  }
};

struct custom_take_range_adaptor {
  template <typename... Args> constexpr auto operator()(Args &&...args) {
    if constexpr (sizeof...(Args) == 1) {
      // this is for only passing count as a parameter
      return custom_take_range_adaptor_closure{args...};
    } else {
      // this is for passing Range & count
      return custom_take_view{std::forward<Args>(args)...};
    }
  }
};

template <std::ranges::viewable_range R, std::invocable<R> Adaptor>
constexpr auto operator|(R &&r, const Adaptor &a) {
  return a(std::forward<R>(r));
}
} // namespace message_NO_EXPORT details
namespace views {
inline details::custom_take_range_adaptor custom_take;
} // namespace views

message_EXPORT void custom_take_check();

} // namespace sp
