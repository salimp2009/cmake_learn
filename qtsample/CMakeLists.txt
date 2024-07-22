cmake_minimum_required(VERSION 3.21)

project(
  helloworld
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(helloworld main.cpp)

target_link_libraries(helloworld PRIVATE Qt6::Core Qt6::Widgets)
