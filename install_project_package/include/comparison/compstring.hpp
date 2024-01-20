#pragma once
#include "messageExport.h"
#include <compare>
#include <cstddef>
namespace sp {

class message_EXPORT String {
private:
  const char *mdata;
  const std::size_t mlen;

public:
  template <std::size_t N> String(const char (&src)[N]) : mdata{src}, mlen{N} {}

  constexpr const char *begin() const { return mdata; }
  constexpr const char *end() const { return mdata + mlen; }
  constexpr auto operator<=>(const String &other) const {
    return compare(*this, other);
  }
  constexpr bool operator==(const String &other) const {
    if (mlen != other.mlen) {
      return false;
    }
    return compare(*this, other) == 0;
  }

private:
  static std::weak_ordering compare(const String &lhs, const String &rhs);
};

} // namespace sp
