cmake_minimum_required(VERSION 3.21)

project(linearAlgrebra LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(
  unpackEigen
  COMMAND ${CMAKE_COMMAND} -E tar xzf
          ${CMAKE_CURRENT_SOURCE_DIR}/eigen-eigen-5a0156e40feb.tar.gz
  COMMAND ${CMAKE_COMMAND} -E rename eigen-eigen-5a0156e40feb eigen-3.3.4
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Unpacking Eigen3 in
${CMAKE_CURRENT_BINARY_DIR}/eigen-3.3.4")

# add_custom_target( unpack-eigen ALL COMMAND ${CMAKE_COMMAND} -E tar -xzf
# ../eigen-eigen-5a0156e40feb.tar.gz COMMAND ${CMAKE_COMMAND} -E rename
# eigen-eigen-5a0156e40feb eigen-3.3.4 WORKING_DIRECTORY
# ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Unpacking Eigen3 in
# ${CMAKE_CURRENT_BINARY_DIR}/eigen-3.3.4")

add_executable(linear-algebra linear-algebra.cpp)
add_dependencies(linear-algebra unpackEigen)
target_include_directories(linear-algebra
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/eigen-3.3.4)
