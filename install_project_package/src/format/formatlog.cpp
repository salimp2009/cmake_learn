#include "formatlog.hpp"
#include <chrono>

namespace sp {

void vlogger(LogLevel level, std::string_view fmt, std::format_args &&args) {
  using namespace std::string_view_literals;
  const auto tm =
      std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
  std::clog << std::format("[level: {}]-[time: {:%F %T }] "sv, level,
                           std::chrono::floor<std::chrono::milliseconds>(tm))
            << std::vformat(fmt, args);
};

// void logger(LogLevel level, std::string_view fmt, const auto &...args) {
//   // auto loc = std::source_location::current();
//   std::cout << std::format(" level:{}", level
//                            /* loc.file_name(), loc.line(), loc.column() */)
//             << std::format(fmt, args...) << '\n';
// }

} // namespace sp
