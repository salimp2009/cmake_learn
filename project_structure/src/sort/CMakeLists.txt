cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(sorted LANGUAGES CXX)

add_library(sort STATIC sort.cpp)
target_include_directories(sort PUBLIC ${CMAKE_SOURCE_DIR}/include/sort)
