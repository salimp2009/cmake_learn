# set minimum cmake version
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# project name and language
project(simple_test LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
include(./function.cmake)
f(1 2 optional1 optional2)

find_package(Python REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)
# find_package(Catch2 REQUIRED)
include(./cmake/CPM.cmake)
cpmaddpackage(NAME Catch2 GITHUB_REPOSITORY catchorg/Catch2 VERSION 3.4.0)

# example library
add_library(sum_integers SHARED sum_integers.cpp)
target_include_directories(sum_integers PUBLIC ${CMAKE_SOURCE_DIR})
# main code
add_executable(sum_up main.cpp)
target_link_libraries(sum_up sum_integers)

# testing binary
add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test sum_integers)

enable_testing()

add_subdirectory(tests)

# enable testing functionality

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
