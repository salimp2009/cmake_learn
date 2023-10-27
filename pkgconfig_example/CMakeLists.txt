cmake_minimum_required(VERSION 3.21)

project(glib_example LANGUAGES CXX C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(glib REQUIRED glib-2.0 IMPORTED_TARGET)

add_executable(mainApp main.cpp)
target_include_directories(mainApp PRIVATE ${glib_INCLUDE_DIR})
target_link_libraries(mainApp PRIVATE PkgConfig::glib)
