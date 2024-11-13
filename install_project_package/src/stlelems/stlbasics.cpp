#include <stlbasics.hpp>

#include <chrono>
#include <print>

namespace sp {
void print_zone_time(std::chrono::sys_days sysdays, std::string_view zone) {
  auto zonetime = std::chrono::zoned_time{zone, sysdays};
  auto info = zonetime.get_info();
  std::print("time info for {:%F} in {}\nabbrev: {}, \nbegin {}, end {},"
             "\noffset {}, save {}\n",
             sysdays, zone, info.abbrev, info.begin, info.end, info.offset,
             info.save);
}

} // end of namespace sp
