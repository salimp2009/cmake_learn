cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(print LANGUAGES CXX)

add_library(print STATIC print.cpp)
target_include_directories(print PUBLIC "${CMAKE_SOURCE_DIR}/include/print")
