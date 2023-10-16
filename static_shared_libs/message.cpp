#include "message.hpp"
#include <iostream>
#include <numeric>
#include <string>

std::ostream &Message::printObject(std::ostream &os) {
  os << "This is my very nice message: " << std::endl;
  os << message_;
  return os;
}

int sum_integers3(const std::vector<int> &integers) {
  auto sum = 0;

  auto result = std::accumulate(std::begin(integers), std::end(integers), sum);
  return result;
}
