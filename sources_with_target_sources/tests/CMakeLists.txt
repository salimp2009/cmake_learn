include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test PRIVATE evolution Catch2::Catch2WithMain)

add_test(NAME test_evolution COMMAND $<TARGET_FILE:cpp_test>)
