#pragma once

#include "messageExport.h"
#include <fmt/core.h>
#include <format>
#include <map>
#include <utility>

namespace sp {
struct message_EXPORT Book {
  std::string title;
  std::string isbn;
};

struct message_EXPORT Price {
  double amount{};
};

struct Magazine {
  std::string name;
  std::string isbn;
};

constexpr inline auto comp_book = [](const Book &a, const Book &b) {
  return a.isbn > b.isbn;
};

using cmp =
    decltype([](const auto &a, const auto &b) { return a.isbn > b.isbn; });

template <typename Value>
using MapBookSortedbyIsbn = std::map<Book, Value, cmp>;

template <typename Key, typename Value = Price>
using MapBookSortedbyIsbn2 = std::map<Key, Value, cmp>;

message_EXPORT void map_books_sort_price();

template <typename First, typename... Args>
void print(First &&first, Args &&...args) {
  fmt::print("[{}]: ", first);
  (fmt::print("{} ", args), ...);
  std::puts("");
}

template <typename... Origins>
message_EXPORT inline constexpr auto getNamedLogger(Origins &&...origins) {
  return
      [... origins = std::forward<Origins>(origins)]<typename... Args>(
          Args &&...args) { print(origins..., std::forward<Args>(args)...); };
}

// message_EXPORT inline auto getNamedLogger(const std::string origin);
} // namespace sp
