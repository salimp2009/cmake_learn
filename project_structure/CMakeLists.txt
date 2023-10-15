cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(sorted LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(src)
