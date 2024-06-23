#include "Message.hpp"
#include "config.hpp"
// #include <iostream>
// #include <ostream>
// #include <string>

#ifdef HAVE_UUID
#include <uuid/uuid.h>
#endif

auto operator<<(std::ostream &os, const Message &obj) -> std::ostream & {
  os << "This is my very nice message: " << '\n'
     << obj.print() << '\n'
     << "git_hash: " << git_sha << " git_status: " << git_status << '\n'
     << " version: " << project_version << '\n'
     << "version major: " << project_version_major
     << " minor: " << project_version_minor << '\n'
     << " patch: " << project_version_patch << '\n'
     << "...and here is its UUID: " << getUUID() << '\n';
  return os;
}

#ifdef HAVE_UUID
std::string getUUID() {
  uuid_t uuid;
  uuid_generate(uuid);
  char uuid_str[37];
  uuid_unparse_lower(uuid, uuid_str);
  uuid_clear(uuid);
  std::string uuid_cxx(uuid_str);
  return uuid_cxx;
}
#else
std::string getUUID() { return "Ooooops, no UUID for you!"; }
#endif

int Test2::get_value2() const { return 5; }

// void use_fmt() { /* fmt::print("using fmt cool {}", 34); */
// }
