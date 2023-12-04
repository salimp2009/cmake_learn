# testing binary cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# # project name and language project(simple_test LANGUAGES CXX)

include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(cpp_test2 test2.cpp)
target_link_libraries(
  cpp_test2 PRIVATE message::message_static message::concepts
                    Catch2::Catch2WithMain)

enable_testing()

add_test(NAME catch_test COMMAND $<TARGET_FILE:cpp_test2> --success)
add_test(NAME integrationTest # CONFIGURATIONS Debug RelWithDebInfo
         COMMAND hello_world_wAR2)
# set_tests_properties(integrationTest PROPERTIES PASS_REGULAR_EXPRESSION 2 3 4
# 5 7)

# this generate files for each test with the prefix and extension given
catch_discover_tests(
  cpp_test2
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
