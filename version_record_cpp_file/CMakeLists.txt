cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(versioncpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")
  file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PROGRAM_VERSION)
  # this is for trimming whitespace
  string(STRIP "${PROGRAM_VERSION}" PROGRAM_VERSION)
else()
  message(FATAL_ERROR "File
${CMAKE_CURRENT_SOURCE_DIR}/VERSION not found")
endif()

# recording git_hash during config time
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

message(STATUS "Git hash is ${GIT_HASH}")

# generate version.hpp based on version.hpp.in
configure_file(version.hpp.in generated/version.hpp @ONLY)

add_executable(record_cppversion example.cpp)

target_include_directories(record_cppversion
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)
