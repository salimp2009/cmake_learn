#include "lambdasort.hpp"
#include "fmt/ranges.h"
#include <fmt/color.h>
#include <fmt/core.h>

namespace sp {

void map_books_sort_price() {
  const Book effective_cpp{"Effective C++", "978-3-16-148410-0"};
  const Book functprogram{"Functional Programming", "978-3-20-148410-0"};

  const Price normal{34.95};
  const Price reduced{24.95};

  MapBookSortedbyIsbn<Price> book_sortedby_price{{effective_cpp, normal},
                                                 {functprogram, reduced}};
  for (const auto &[key, value] : book_sortedby_price) {
    fmt::print(fmt::emphasis::bold | fg(fmt::terminal_color::yellow),
               "bookmap sorted by price: {} {}\n", key.title, value.amount);
  }

  fmt::print(fmt::emphasis::reverse | fg(fmt::color::yellow_green),
             "Elapsed time: {0:.2f} seconds\n", 1.23);
}
} // namespace sp
