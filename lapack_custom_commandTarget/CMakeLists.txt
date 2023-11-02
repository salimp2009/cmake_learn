cmake_minimum_required(VERSION 3.21)

project(linearAlgrebra LANGUAGES CXX Fortran)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(./cmake/CPM.cmake)
cpmaddpackage(
  NAME LAPACK VERSION 3.11.0 URL
  https://github.com/Reference-LAPACK/lapack/archive/refs/tags/v3.11.0.tar.gz)

add_subdirectory(deps)

add_executable(linear-algebra linear-algebra.cpp)
target_link_libraries(linear-algebra PRIVATE math)
