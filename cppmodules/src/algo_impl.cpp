module;
#include <config.hpp>
#include <fmt/core.h>
#include <print>
// #include <tuple>
import std;
module algo;
void Algo::helloWorld() { fmt::print("{} world\n", "hello"); }

template <auto, typename> struct tuple_element_sp;

template <std::size_t I, class... Ts>
struct tuple_element_sp<I, std::tuple<Ts...>> {
  using type = Ts...[I];
};
