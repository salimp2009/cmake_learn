#include "rangebase.hpp"
#include <algorithm>
#include <fmt/ranges.h>
// #include <fmt/core.h>
#include <ranges>
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

void add_currency() {
  const std::vector prices{3.95, 6.0, 95.4, 10.95, 12.90, 5.50};

  // const char* for suffix works but std::string_view suffix dont work
  auto add_suffix = [](const std::string &suffix) {
    return [suffix](auto &&val) { return std::to_string(val) + suffix; };
  };

  auto subView = prices |
                 std::views::filter([](auto &&val) { return val < 10.; }) |
                 std::views::transform(add_suffix("$"));
  fmt::println("prices with currencies: {}", subView);
}

} // namespace sp
