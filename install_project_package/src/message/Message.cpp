#include "Message.hpp"

#include <iostream>
#include <ostream>
#include <string>

#ifdef HAVE_UUID
#include <uuid/uuid.h>
#endif

std::ostream &operator<<(std::ostream &os, const Message &obj) {
  os << "This is my very nice message: " << '\n'
     << obj.print() << '\n'
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
