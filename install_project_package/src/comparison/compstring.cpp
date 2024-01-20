#include "compstring.hpp"
#include <algorithm>
#include <compare>

namespace sp {

std::weak_ordering String::compare(const String &lhs, const String &rhs) {

  if (lhs.mlen == rhs.mlen &&
      std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) {
    return std::weak_ordering::equivalent;
  }

  if (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                   rhs.end())) {
    return std::weak_ordering::less;
  }

  return std::weak_ordering::greater;
}

} // namespace sp
