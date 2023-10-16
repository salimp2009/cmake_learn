#pragma once
#include <iosfwd>
#include <string>
#include <vector>

class Message {
 public:
  explicit Message(const std::string &m) : message_(m) {}
  friend std::ostream &operator<<(std::ostream &os, Message &obj) {
    return obj.printObject(os);
  }

 private:
  std::string message_;
  std::ostream &printObject(std::ostream &os);
};

int sum_integers3(std::vector<int> &integers);
