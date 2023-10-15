cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(print LANGUAGES CXX)

add_library(print STATIC print.cpp)
target_include_directories(print PUBLIC "${CMAKE_SOURCE_DIR}/include/print")

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET print ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()
