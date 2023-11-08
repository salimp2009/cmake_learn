# testing binary cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# # project name and language project(simple_test LANGUAGES CXX)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test PRIVATE sum_integers Catch2::Catch2WithMain)

enable_testing()

add_test(NAME catch_test COMMAND $<TARGET_FILE:cpp_test> --success)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(add_catch_test)
add_catch_test(short 1.5)
add_catch_test(long 2.5 extra_args)

message(STATUS "in total there were ${num_macro_calls} calls to add_catch_test")
add_test(
  NAME integrationTest
  CONFIGURATIONS Debug RelWithDebInfo
  COMMAND sum_up 1 2 4)
set_tests_properties(integrationTest PROPERTIES PASS_REGULAR_EXPRESSION 7)

# this generate files for each test with the prefix and extension given
catch_discover_tests(
  cpp_test
  TEST_PREFIX
  "catch2tests."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "catch2tests."
  OUTPUT_SUFFIX
  .xml)
