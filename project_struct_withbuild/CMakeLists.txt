cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(sorted LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# just set it to test purposes. Do not set it  leave it to user default is /usr/
set(CMAKE_INSTALL_PREFIX "/home/salim/repos/cpp_sandbox/cmake_learn/temp")
message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." ON)
option(ENABLE_COVERAGE "Enable a Code Coverage build." OFF)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." ON)
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

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
  include(sanitizer)
  add_sanitizer_flags()
endif()

include(./cmake/CPM.cmake)
cpmaddpackage(NAME Catch2 GITHUB_REPOSITORY catchorg/Catch2 VERSION 3.4.0)

# include(FetchContent) FetchContent_Declare( googletest GIT_REPOSITORY
# https://github.com/google/googletest.git GIT_TAG v1.14.0)

# FetchContent_GetProperties(googletest) # all the remaining CMake code will be

# if(NOT googletest_POPULATED) FetchContent_Populate(googletest)
#
# # Prevent GoogleTest from overriding our compiler/linker options when building
#
# # with Visual Studio
#
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# # Prevent GoogleTest from using PThreads

# set(gtest_disable_pthreads ON CACHE BOOL "" FORCE) # adds the targers: gtest,
# gtest_main, gmock, gmock_main
#
# add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}) # placed #
# here # Silence std::tr1 warning on MSVC
#
# if(MSVC) foreach(_tgt gtest gtest_main gmock gmock_main)
# target_compile_definitions( ${_tgt} PRIVATE
# "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING") endforeach() endif() endif()

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

# installing project header files install(FILES include/sort/sort.hpp
# DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}/sort)

# install(FILES include/print/print.hpp DESTINATION
# ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}/print)

# install(FILES include/sort/sum_vector.hpp DESTINATION
# ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}/sort)
# include(GNUInstallDirs)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  # TYPE INCLUDE
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}
  PATTERN "*.in" EXCLUDE)

install(
  TARGETS sort print
  EXPORT export_sorted
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_PROJECT_NAME}/)

install(
  EXPORT export_sorted
  FILE ${CMAKE_PROJECT_NAME}-config.cmake
  NAMESPACE sorted::
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_PROJECT_NAME}/)

add_custom_target(
  uninstall COMMAND ${CMAKE_COMMAND} -P
                    ${PROJECT_SOURCE_DIR}/cmake/UninstallHelper.cmake)
