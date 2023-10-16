cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(sorted LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." ON)
option(ENABLE_COVERAGE "Enable a Code Coverage build." OFF)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." ON)

option(ENABLE_LTO "Enable to add Link Time Optimization." ON)

# CMAKE MODULES
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

if(ENABLE_WARNINGS)
  include(warnings)
endif()

if(ENABLE_LTO)
  include(lto)
endif()

add_subdirectory(src)
