# set minimum cmake version
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# project name and language
project(
  simple_test
  VERSION "${VERSION}"
  LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
include(./function.cmake)
read_semver(
  DEBUG_INFO
  SPLIT
  OUTPUT_VARIABLE_NAME
  "VERSION"
  FILE_NAME
  "Version"
  MV
  a
  b
  c
  d
  e)

message("VERSION_MAJOR= ${VERSION_MAJOR}")
message("VERSION_MINOR= ${VERSION_MINOR}")
message("VERSION_MAJOR= ${VERSION_PATCH}")
message("VERSION= ${VERSION}")

f(1 2 optional1 optional2)

find_package(Python REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)
# find_package(Catch2 REQUIRED)
include(./cmake/CPM.cmake)
cpmaddpackage(NAME Catch2 GITHUB_REPOSITORY catchorg/Catch2 VERSION 3.4.0)

# example library
add_library(sum_integers SHARED sum_integers.cpp)
target_include_directories(
  sum_integers PUBLIC $<INSTALL_INTERFACE:include>
                      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")
if(ENABLE_UNIT_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0)

  FetchContent_GetProperties(googletest) # all the remaining CMake code will be

  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    # Prevent GoogleTest from overriding our compiler/linker options when
    # building with Visual Studio
    set(gtest_force_shared_crt
        ON
        CACHE BOOL "" FORCE)
    # Prevent GoogleTest from using PThreads
    set(gtest_disable_pthreads
        ON
        CACHE BOOL "" FORCE)
    # adds the targers: gtest, gtest_main, gmock, gmock_main
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}) # placed
                                                                        # here
    # Silence std::tr1 warning on MSVC
    if(MSVC)
      foreach(_tgt gtest gtest_main gmock gmock_main)
        target_compile_definitions(
          ${_tgt} PRIVATE "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")
      endforeach()
    endif()
  endif()
endif()

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
