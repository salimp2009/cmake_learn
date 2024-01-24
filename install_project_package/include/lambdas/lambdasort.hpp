#pragma once

#include "messageExport.h"
#include <map>
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

} // namespace sp
