#include "lambdabasics.hpp"
#include "lambdacaptures.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace sp {

void lambda_basics1() noexcept {
  std::puts("-------------> lambda_basics1 test -------------<");
  SomeCaptures obj1{};
  auto result = obj1.double_val();
  fmt::println("Somecaptures: double_val: {}", result);
  std::puts("-------------> lambda_basics1 test passed -------------<");
}
} // namespace sp
