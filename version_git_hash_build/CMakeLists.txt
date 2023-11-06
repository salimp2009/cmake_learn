cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(githashbuild LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(record_cppversion example.cpp)

target_include_directories(record_cppversion
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hpp ALL
  COMMAND ${CMAKE_COMMAND} -D TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} -P
          ${CMAKE_CURRENT_SOURCE_DIR}/cmake/git-hash.cmake
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(get_git_hash ALL
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hpp)
# make sure version.hpp generated before we build the executable
add_dependencies(record_cppversion get_git_hash)
