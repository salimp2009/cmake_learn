#pragma once

#include <iosfwd>
#include <iostream>
#include <string>

#include <coroutine>
#include <messageExport.h>

class message_EXPORT Message {
public:
  explicit Message(std::string m) : message_(std::move(m)) {}

  const std::string &print() const & { return this->message_; }

private:
  std::string message_;
  // std::ostream &printObject(std::ostream &os);
};

std::string getUUID();

std::ostream message_EXPORT &operator<<(std::ostream &os, const Message &obj);
