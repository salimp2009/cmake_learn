cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(sorted LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CXX_BASIC_FLAGS "-g3" "-O1")

include(CheckCXXCompilerFlag)
set(ASAN_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_REQUIRED_FLAGS ${ASAN_FLAGS})

check_cxx_compiler_flag(${ASAN_FLAGS} asan_works)
unset(CMAKE_REQUIRED_FLAGS)

if(asan_works)
  string(REPLACE " " ";" _asan_flags ${ASAN_FLAGS})
  message(STATUS "asan works: ${asan_works}")
  add_executable(asan_example asan-example.cpp)

  target_compile_options(asan_example PUBLIC ${CXX_BASIC_FLAGS} ${_asan_flags})
  # _asan_flag needs to be added to compiler and linker
  target_link_libraries(asan_example PUBLIC ${_asan_flags})
endif()
