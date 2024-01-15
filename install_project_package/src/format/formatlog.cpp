#include "formatlog.hpp"
#include <ctime>
#include <source_location>
// #include <iostream>

namespace sp {

void vlogger(LogLevel level, std::string_view fmt, std::format_args &&args) {
  using namespace std::string_view_literals;

  std::clog << std::format("LOG LEVEL: {} "sv, level) << std::vformat(fmt, args)
            << '\n';
};

// void logger(LogLevel level, std::string_view fmt, const auto &...args) {
//   // auto loc = std::source_location::current();
//   std::cout << std::format(" level:{}", level
//                            /* loc.file_name(), loc.line(), loc.column() */)
//             << std::format(fmt, args...) << '\n';
// }

} // namespace sp
