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

foreach(currentElem RANGE 0 9)
  message("curren Range elem: ${currentElem}")
endforeach()

foreach(ce1 ce2 IN ZIP_LISTS ListA ListB)
  message("curren zip_lists element: [${ce1} ${ce2}]")
endforeach()

set(USE_DEBUG_CODE ON)
if(USE_DEBUG_CODE)
  message("Using debug code : ${USE_DEBUG_CODE}")
else()
  message("Using release code : ${USE_DEBUG_CODE}")
endif()

add_executable(use_uuid_asm use-uuid.cpp)
# -save-temps=obj create assembly file, object file and ii file -asm=intel
# generates the assembly with intel instructions otherwise it is ATT
target_compile_options(use_uuid_asm PRIVATE -save-temps=obj -masm=intel
                                            -fsanitize=address,undefined)

target_link_libraries(use_uuid_asm
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)
target_link_options(use_uuid_asm PUBLIC -fsanitize=address,undefined)
