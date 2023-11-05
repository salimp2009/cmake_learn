cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(
  versionc
  VERSION 2.0.1
  LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(version.h.in generated/version.h @ONLY)

add_executable(record_cversion version_c.c)

target_include_directories(record_cversion
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)
