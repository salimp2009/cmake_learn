#pragma once

#include "messageExport.h"
#include <map>
namespace sp {
struct message_EXPORT Book {
  std::string title;
  std::string isbn;
};

struct Price {
  double amount{};
};

constexpr inline auto comp_book = [](const Book &a, const Book &b) {
  return a.isbn > b.isbn;
};

template <typename Value>
using MapBookSortedbyIsbn = std::map<Book, Value, decltype(comp_book)>;
message_EXPORT void map_books_sort_price();

} // namespace sp
