cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(
  message-package_project
  VERSION 1.2.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# just set it to test purposes. Do not set it  leave it to user default is /usr/
set(CMAKE_INSTALL_PREFIX "/home/salim/repos/cpp_sandbox/cmake_learn/temp/")
message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      RelWithDeb
      CACHE STRING "Build type" FORCE)
endif()

include_guard(GLOBAL)

# set build subdirectories & install directories
include(GNUInstallDirs)
include(cmake/set_build_install_dir.cmake)
set_build_install_dirs()

include(cmake/CPM.cmake)
cpmaddpackage(NAME Catch2 GITHUB_REPOSITORY catchorg/Catch2 VERSION 3.4.0)
cpmaddpackage(
  NAME
  fmt
  GIT_TAG
  10.1.1
  GITHUB_REPOSITORY
  fmtlib/fmt
  OPTIONS
  "CMAKE_POSITION_INDEPENDENT_CODE ON")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(StandartProjectSettings)
standartprojectsettings()

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(SUBSTRING "${GIT_SHA}" 0 8 GIT_SHORT_SHA)

include(CMakeDependentOption)
option(ENABLE_HARDENING "Enable hardening" ON)
cmake_dependent_option(
  ENABLE_GLOBAL_HARDENING
  "Attempt to push hardening options to built dependencies" ON ENABLE_HARDENING
  OFF)

if(PROJECT_IS_TOP_LEVEL)
  option(ENABLE_DOXYGEN "Generate Doxygen Docs for project" OFF)

  option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
  option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

  option(ENABLE_TESTING "Enable a Unit Testing build." ON)
  option(ENABLE_COVERAGE "Enable a Code Coverage build." OFF)

  option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

  option(ENABLE_SANITIZE_ADDR "Enable address sanitize." ON)
  option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." ON)
  option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
  option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

  option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)
  option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." ON)

  option(ENABLE_LTO "Enable to add Link Time Optimization." ON)
endif()

if(ENABLE_HARDENING OR ENABLE_GLOBAL_HARDENING)
  include(Hardening)
endif()

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

# project version generated in config.hpp
add_subdirectory(configured)

add_subdirectory(src)

# add_dependencies(hello_world_wDSO2 get_git_hash)

enable_testing()

add_subdirectory(tests)

include(CMakeCPack.cmake)

# this is the older way of generating doxygen Doxyfile.in prefer the
# doxygenSetup

# if(ENABLE_DOXYGEN) include(UseDoxygenDoc) endif()

# add_doxygen_doc( BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/_build DOXY_FILE
# ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in TARGET_NAME docs COMMENT "HTML
# Documentation")

if(ENABLE_DOXYGEN)
  include(doxygenSetup)

  # input directory and output directory for doxygen

  generate_doxygen("${CMAKE_CURRENT_LIST_DIR}/include;
${CMAKE_CURRENT_LIST_DIR}/src" "${CMAKE_CURRENT_LIST_DIR}/docs/doxygen") #

  # option to generate docs every build time; not recommended; it will slow down
  # build time

  # add_dependencies(hello_world_wAR2 doxygen)
endif()
