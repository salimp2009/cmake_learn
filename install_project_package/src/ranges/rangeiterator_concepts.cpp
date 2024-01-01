#include "rangeiterator_concepts.hpp"
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <ranges>
#include <vector>

namespace sp {

void ranges_type_checks() {
  static_assert(continuesRange<std::vector<int>> &&
                randomaccessRange<std::vector<int>>);

  static_assert(continuesRange<std::array<int, 1>> &&
                randomaccessRange<std::array<int, 1>>);

  static_assert(not continuesRange<std::list<int>> &&
                not randomaccessRange<std::list<int>>);

  static_assert(not continuesRange<std::vector<bool>> &&
                randomaccessRange<std::vector<bool>>);

  static_assert(not continuesRange<std::deque<int>> &&
                randomaccessRange<std::deque<int>>);

  static_assert(std::ranges::sized_range<std::array<int, 1>>);
  static_assert(std::ranges::sized_range<std::list<int>>);
  static_assert(not std::ranges::sized_range<std::forward_list<int>>);
  static_assert(std::ranges::sized_range<std::vector<int>>);

  static_assert(bidirectionalRange<std::vector<int>>);
  static_assert(bidirectionalRange<std::array<int, 1>>);
  static_assert(bidirectionalRange<std::list<int>>);
  static_assert(not bidirectionalRange<std::forward_list<int>>);
}
} // namespace sp
