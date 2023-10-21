enable_testing()

# testing binary
add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test sum_integers)

add_test(NAME setup COMMAND ${Python_EXECUTABLE}
                            ${CMAKE_CURRENT_SOURCE_DIR}/setup.py)
set_tests_properties(setup PROPERTIES FIXTURES_SETUP my-fixture)

add_test(NAME feature-a COMMAND ${Python_EXECUTABLE}
                                ${CMAKE_CURRENT_SOURCE_DIR}/feature-a.py)
add_test(NAME feature-b COMMAND ${Python_EXECUTABLE}
                                ${CMAKE_CURRENT_SOURCE_DIR}/feature-b.py)

set_tests_properties(feature-a feature-b PROPERTIES FIXTURES_REQUIRED
                                                    my-fixture)
add_test(NAME cleanup COMMAND ${Python_EXECUTABLE}
                              ${CMAKE_CURRENT_SOURCE_DIR}/cleanup.py)
set_tests_properties(cleanup PROPERTIES FIXTURES_CLEANUP my-fixture)

# define tests
add_test(NAME bash_test
         COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh
                 $<TARGET_FILE:sum_up>)

add_test(NAME cpp_test COMMAND $<TARGET_FILE:cpp_test>)

add_test(NAME python_test_long
         COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py
                 --executable $<TARGET_FILE:sum_up>)

add_test(NAME python_test_short
         COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py
                 --short --executable $<TARGET_FILE:sum_up>)

# example to how temporarily disable test that fails until fixed
add_test(NAME fail_example COMMAND ${Python_EXECUTABLE}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/test2.py)

set_tests_properties(fail_example PROPERTIES WILL_FAIL true)
