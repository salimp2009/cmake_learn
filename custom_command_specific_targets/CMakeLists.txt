cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(fortransize LANGUAGES Fortran)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Build type" FORCE)
endif()

add_executable(example_fortran "")

target_sources(example_fortran PRIVATE example.f90)

add_custom_command(
  TARGET example_fortran
  PRE_LINK
  COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/echo-file.py
          ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/example_fortran.dir/link.txt
  COMMENT "link line:"
  VERBATIM)

add_custom_command(
  TARGET example_fortran
  POST_BUILD
  COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/static_size.py
          $<TARGET_FILE:example_fortran>
  COMMENT "static size of executable: "
  VERBATIM)
