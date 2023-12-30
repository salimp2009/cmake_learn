#include "rangebase.hpp"
#include "fmt/ranges.h"
#include <algorithm>
#include <fmt/core.h>
#include <format>
#include <vector>
namespace sp {
void sort_by_title() {
  std::vector<Book> books{
      {"Functional Programming in C++", "978-3-20-148410-0"},
      {"Effective C++", "978-3-16-148410-0"}};

  std::ranges::sort(books, {}, &Book::title);
  fmt::println("sorted by title: {}", books);
}
void sort_by_isbn() {
  std::vector<Book> books{
      {"Functional Programming in C++", "978-3-20-148410-0"},
      {"Effective C++", "978-3-16-148410-0"}};

  std::ranges::sort(books, std::ranges::greater{}, &Book::isbn);
  fmt::println("sorted by isbn: {}", books);
}

} // namespace sp
