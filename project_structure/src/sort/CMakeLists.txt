cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(sorted LANGUAGES CXX)

add_library(sort STATIC sort.cpp)
target_include_directories(sort PUBLIC "${CMAKE_SOURCE_DIR}/include/sort")

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET sort ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()
# target_include_directories( sort PUBLIC
# $<BUILD_INTERFACE:${sort_BINARY_DIR}/${CMAKE_SOURCE_DIR}/include/sort>
# $<BUILD_INTERFACE:${sort_SOURCE_DIR}/${CMAKE_SOURCE_DIR}/include/sort>
# $<INSTALL_INTERFACE:include/sort>)
