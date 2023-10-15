cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(sorted LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

if(ENABLE_WARNINGS)
  include(warnings)
endif()

add_subdirectory(src)
