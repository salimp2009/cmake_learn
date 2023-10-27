#include <bit>
#include <glib.h>
#include <iostream>
#include <memory>

int main() {
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
