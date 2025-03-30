module;
// #include <fmt/core.h>
#include <config.hpp>
#include <string>
export module algo;
// import std;
// using fmt::print;
export struct Algo {
public:
  // Algo() = default;
  // ~Algo() = default;
  void helloWorld();
};

namespace util {
export std::string path = "...";
}
