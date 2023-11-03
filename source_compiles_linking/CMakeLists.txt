cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(probcompilation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenMP)

if(OpenMP_FOUND)
  set(_scratch_dir ${CMAKE_CURRENT_BINARY_DIR}/omp_try_compile)
  try_compile(
    omp_taskloop_test_1 ${_scratch_dir}
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/taskloop.cpp
    LINK_LIBRARIES OpenMP::OpenMP_CXX)
  message(STATUS "Result of try_compile: ${omp_taskloop_test_1}")

  include(CheckCXXSourceCompiles)

  file(READ ${CMAKE_CURRENT_SOURCE_DIR}/taskloop.cpp _snippet)
  set(CMAKE_REQUIRED_LIBRARIES OpenMP::OpenMP_CXX)

  check_cxx_source_compiles("${_snippet}" omp_taskloop_test_2)
  unset(CMAKE_REQUIRED_LIBRARIES)
  message(STATUS "Result of check_cxx_source_compiles:
  ${omp_taskloop_test_2}")
else()
  message(STATUS "OpenMP not found: no test for taskloop is run")
endif()
