#include "conversion.hpp"

#include <bitset>
#include <string>

std::string binary_representation(int decimal) {
  return std::bitset<8>(decimal).to_string();
}
