cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(usefindpackage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_INSTALL_PREFIX /home/salim/repos/cpp_sandbox/cmake_learn)
# message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

find_package(sorted PATHS /home/salim/repos/cpp_sandbox/cmake_learn REQUIRED)

add_executable(usesort main.cpp)
# target_link_libraries(usesort PRIVATE sorted::sort sorted::print)
target_link_libraries(usesort PRIVATE sort print)
