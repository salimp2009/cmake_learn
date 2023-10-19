add_executable(cpp_test3 "")
target_sources(cpp_test3 PRIVATE test3.cpp)
target_link_libraries(cpp_test3 PRIVATE sum_integers gtest_main)

enable_testing()

add_test(NAME google_test COMMAND $<TARGET_FILE:cpp_test3>)

# this generate files for each test with the prefix and extension given
catch_discover_tests(
  cpp_test3
  TEST_PREFIX
  "googletests."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "googletests."
  OUTPUT_SUFFIX
  .xml)
