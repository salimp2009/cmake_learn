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

find_package(LAPACK REQUIRED)
#
set(wrap_BLAS_LAPACK_sources
    ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxBLAS.hpp
    ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxBLAS.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxLAPACK.hpp
    ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxLAPACK.cpp)

add_custom_command(
  OUTPUT ${wrap_BLAS_LAPACK_sources}
  COMMAND ${CMAKE_COMMAND} -E tar xzf
          ${CMAKE_CURRENT_SOURCE_DIR}/wrap_BLAS_LAPACK.tar.gz
  COMMAND ${CMAKE_COMMAND} -E touch ${wrap_BLAS_LAPACK_sources}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/wrap_BLAS_LAPACK.tar.gz
  COMMENT "Unpacking C++ wrappers for BLAS/LAPACK"
  VERBATIM)

add_library(math "")
target_sources(
  math
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxBLAS.cpp
          ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxLAPACK.cpp
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxBLAS.hpp
         ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK/CxxLAPACK.hpp)
target_include_directories(
  math INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/wrap_BLAS_LAPACK)
target_link_libraries(math PUBLIC ${LAPACK_LIBRARIES})

add_executable(linear-algebra linear-algebra.cpp)
target_link_libraries(linear-algebra PRIVATE math)
