#include <Message.hpp>
// #include <conceptbasics.hpp>
#include "aggregbasics.hpp"
#include "compbasics.hpp"
#include "conceptbasics_check.hpp"
#include "corobasics.hpp"
#include "formatbasics.hpp"
#include "lambdabasics.hpp"
#include "lambdasort.hpp"
#include "nttpbasics.hpp"
#include "rangebasics.hpp"
#include "rangeiterator_concepts.hpp"
#include "stlbasics.hpp"

#include <cstdlib>

#include <print>

int main() {
  Message say_hello("Hello, CMake World!");

  std::cout << say_hello << '\n';
  auto myval = 5;
  std::print("say hello {}", myval);

  Message say_goodbye("Goodbye, CMake World");
  std::cout << say_goodbye << '\n';
  // static_assert(not sp::are_same_v<decltype(1), decltype(2.4)>);
  // static_assert(not are_same2<decltype(1), decltype(2.4)>);

  [[maybe_unused]] Test2 tst2{};
  tst2.value2 = 7;
  // this will not compile since it is invisible in. Message.cpp
  // auto result2 = tst2.get_value2();

  // wont compile since it is not export using message_EXPORT
  // getUUID();

  // visibility check for concepts library; NOT Working
  sp::Test tst{};
  tst.value = 5;
  // this respects visibility since the definition of member function is in
  // conceptbasics.cpp
  // tst.get_value();

  // sp::getnumber();

  // getUUID();

  sp::concepts_basics1();
  sp::concepts_test_stub();
  sp::concepts_constexpr_functions();
  sp::concepts_auto_variables();
  sp::concept_validate_data();
  sp::concept_optional_noncopiable();
  sp::concept_subsumption_rules();
  sp::coroutines_basics1();
  sp::coroutines_stream();
  sp::coroutines_stream_v2();
  sp::range_basics1();
  sp::range_sort_projection();
  sp::range_add_currency();
  sp::ranges_type_checks();
  sp::range_customs_views1();
  sp::format_basics1();
  sp::format_basics2();
  sp::format_to_buffer();
  sp::print_indices();
  sp::color_test_hex();
  sp::custom_buffer();
  sp::logger_format();
  sp::comp_basics1();
  sp::lambda_basics1();
  sp::lambda_maps_sorted();
  sp::lambda_variadic_args();
  sp::aggregate_basics1();
  sp::nttp_basics1();
  sp::safe_printf();
  sp::stlchanges_basics1();
  sp::time_zone_basics1();
  sp::local_time_basics();
  return EXIT_SUCCESS;
}
