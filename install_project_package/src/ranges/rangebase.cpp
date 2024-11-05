#include "rangebase.hpp"
#include <algorithm>
#include <print>
#include <ranges>
#include <vector>
namespace sp {
void sort_by_title() {
  std::vector<Book> books{
      {"Functional Programming in C++", "978-3-20-148410-0"},
      {"Effective C++", "978-3-16-148410-0"}};

  std::ranges::sort(books, {}, &Book::title);
  // std::println("sorted by title: {}", books);
}
void sort_by_isbn() {
  std::vector<Book> books{
      {"Functional Programming in C++", "978-3-20-148410-0"},
      {"Effective C++", "978-3-16-148410-0"}};

  std::ranges::sort(books, std::ranges::greater{}, &Book::isbn);
  for (const auto &isbnsorted : books)
    std::println("sorted by isbn: {}", isbnsorted);
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
  for (const auto &price : subView) {
    std::println("prices with currencies: {}", price);
  }
}

} // namespace sp
