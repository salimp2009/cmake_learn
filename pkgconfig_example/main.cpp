#include <bit>
#include <glib.h>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <ranges>
#include <thread>

auto threadfunct1() -> void {
  for (const auto &i : std::views::iota(0, 100)) {
    std::cout << "f1" << '\n';
  }
}

auto threadfunct2() -> void {
  for (const auto i : std::views::iota(0, 100)) {
    std::cout << "f2" << '\n';
  }
}

int main() {
  std::thread t1(threadfunct1);
  std::thread t2(threadfunct2);
  t1.join();
  t2.join();

  auto lstptr = std::make_unique<GList>(GList{});
  GList *list = nullptr;
  char const *hello = "hello glib";
  [[maybe_unused]] GList const *listptr =
      g_list_append(lstptr.get(), std::bit_cast<char *>(hello));
  list = g_list_append(list, std::bit_cast<char *>(hello));
  std::cout << "lstptr = " << lstptr->data << '\n';
  std::cout << "list (GLib*) = " << static_cast<char *>(list->data) << '\n';

  return 0;
}
