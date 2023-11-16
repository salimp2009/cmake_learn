#pragma once

#include <iosfwd>
#include <iostream>
#include <string>
class Message {
public:
  explicit Message(std::string m) : message_(std::move(m)) {}

  const std::string &print() const & { return this->message_; }

private:
  std::string message_;
  // std::ostream &printObject(std::ostream &os);
};

std::string getUUID();

std::ostream &operator<<(std::ostream &os, const Message &obj);
