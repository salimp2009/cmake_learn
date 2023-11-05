cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(uuid_check LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED QUIET)
pkg_search_module(UUID REQUIRED uuid IMPORTED_TARGET)
if(TARGET PkgConfig::UUID)
  message(STATUS "Found libuuid")
endif()

if(UUID_FOUND)
  include(CMakePrintHelpers)
  cmake_print_properties(TARGETS PkgConfig::UUID
                         PROPERTIES INTERFACE_LINK_LIBRARIES)
endif()

include(CheckCSourceRuns)
set(_test_uuid
    "
#include <uuid/uuid.h>

int main(int argc, char * argv[]) {
 uuid_t uuid;
 uuid_generate(uuid);
 return 0;
}
")

set(CMAKE_REQUIRED_LIBRARIES PkgConfig::UUID)
check_c_source_runs("${_test_uuid}" __runs)
unset(CMAKE_REQUIRED_LIBRARIES)

if(NOT __runs)
  message(FATAL_ERROR "Cannot run a simple C executable using libuuid")
endif()

add_executable(use_uuid use-uuid.cpp)

target_link_libraries(use_uuid PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)

foreach(currentElem a b c d e f)
  message("current element: ${currentElem}")
endforeach()

foreach(currentElem IN ITEMS a b c d e f)
  message("current items element: ${currentElem}")
endforeach()

set(ListA 1 2 3 4)
set(ListB 5 6 7 8)
foreach(
  currentElem IN
  LISTS ListA ListB
  ITEMS x y)
  message("current list element: ${currentElem}")
endforeach()

add_executable(use_uuid_asm use-uuid.cpp)
target_compile_options(use_uuid_asm PUBLIC -g -S)

target_link_libraries(use_uuid_asm
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)
target_link_options(use_uuid_asm PUBLIC -g -S)
