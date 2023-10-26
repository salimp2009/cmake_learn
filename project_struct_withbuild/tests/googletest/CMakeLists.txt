add_executable(test_google "")
target_sources(test_google PRIVATE test3.cpp)
target_link_libraries(test_google PRIVATE sorted::sort sorted::print gtest_main
                                          gmock_main)

enable_testing()

add_test(NAME googletest1 COMMAND $<TARGET_FILE:test_google>)
