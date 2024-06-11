# define minimum cmake version
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
# project name and supported language
project(mixedlang LANGUAGES CXX)

# require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# specify where to place libraries
include(GNUInstallDirs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# interface and sources
add_subdirectory(account)

# turn on testing
enable_testing()

# require python
find_package(PythonInterp REQUIRED)

add_test(
  NAME
    python_test
  COMMAND
  
    ${CMAKE_COMMAND} -E env ACCOUNT_MODULE_PATH=${CMAKE_CURRENT_SOURCE_DIR}
                            ACCOUNT_HEADER_FILE=${CMAKE_CURRENT_SOURCE_DIR}/account/account.h
                            ACCOUNT_LIBRARY_FILE=$<TARGET_FILE:account>
    ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/account/test.py
  )
