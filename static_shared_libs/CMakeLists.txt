cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-03 LANGUAGES CXX)
#
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(./cmake/CPM.cmake)
cpmaddpackage(
  NAME Eigen VERSION 3.4.1 URL
  https://gitlab.com/libeigen/eigen/-/archive/3.4.1/eigen-3.4.1.tar.gz
  # Eigen's CMakelists are not intended for library use
)

if(Eigen_ADDED)
  add_library(Eigen INTERFACE IMPORTED)
  target_include_directories(Eigen INTERFACE ${Eigen_SOURCE_DIR})
endif()

cpmaddpackage("gh:TheLartians/PackageProject.cmake@1.9.0")

if(EXISTS "$ENV{HOME}/.cache/CPM/boost_1_83")
  set(FETCHCONTENT_SOURCE_DIR_BOOST
      "$ENV{HOME}/.cache/CPM/boost_1_83_0"
      CACHE PATH "Boost source DIR")
endif()

cpmaddpackage(
  NAME boost-cmake GITHUB_REPOSITORY ClausKlein/boost-cmake GIT_TAG
  b7c741f42b089117221622c72783d2cb821843dc # feature/upgrade-to-boost-v1.79-0
)

# set(CMAKE_GENERATOR "Ninja Multi-Config") Compilers in system

message(STATUS "Is the C++ compiler loaded? ${CMAKE_CXX_COMPILER_LOADED}")
if(CMAKE_CXX_COMPILER_LOADED)
  message(STATUS "The C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "Is the C++ from GNU? ${CMAKE_COMPILER_IS_GNUCXX}")
  message(STATUS "The C++ compiler version is: ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

message(STATUS "C++ flags, Debug configuration:
${CMAKE_CXX_FLAGS_DEBUG}")

message(STATUS "C++ flags, Release configuration:
${CMAKE_CXX_FLAGS_RELEASE}")

message(STATUS "C++ flags, Release configuration with Debug info:
${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

message(STATUS "C++ flags, minimal Release configuration:
${CMAKE_CXX_FLAGS_MINSIZEREL}")

# objects can be used later to create static or shared objects
add_library(message-objects OBJECT message.hpp message.cpp)

option(USE_LIBRARY "Set the value on for static linking" On)
message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND sources message.hpp message.cpp)

list(APPEND flags "-fPIC" "-Wall")
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

set_target_properties(message-objects PROPERTIES POSITION_INDEPENDENT_CODE 1)

set(COMPILER_FLAGS)
set(COMPILER_FLAGS_DEBUG)
set(COMPILER_FLAGS_RELEASE)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND CXX_FLAGS "-std=c++2b" "-fno-rtti" "-fno-exceptions")
  list(APPEND CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods"
       "-Wsuggest-override")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  list(
    APPEND
    CXX_FLAGS
    "-std=c++23"
    "-fno-rtti"
    "-fno-exceptions"
    "-Qunused-arguments"
    "-fcolor-diagnostics")
  list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()

find_package(Python ${PYTHON_VERSION_MAJOR} ${PYTHON_VERSION_MINOR} REQUIRED)
find_package(Python COMPONENTS Interpreter Development Development.Embed)

if(USE_LIBRARY)
  # add_library will create static lib
  add_library(message STATIC ${sources})
  set_target_properties(message PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)
  target_compile_options(
    message
    PRIVATE ${flags} ${CXX_FLAGS} "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
            "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>")

  add_executable(my_message main.cpp)
  target_include_directories(my_message PRIVATE ${PYTHON_INCLUDE_DIRS}
                                                ${Python_LIBRARY_DIRS})
  set_target_properties(
    my_message
    PROPERTIES CXX_STANDARD 23
               CXX_EXTENSIONS OFF
               CXX_STANDART_REQUIRED ON)
  target_compile_options(
    my_message
    PRIVATE "-fPIC" ${CXX_FLAGS} "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
            "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>")

  target_link_libraries(
    my_message
    PUBLIC message
    PRIVATE Eigen3::Eigen ${Python_LIBRARIES} Boost::filesystem)

else()
  add_executable(my_message main.cpp ${sources})
  set_target_properties(
    message
    PROPERTIES CXX_STANDARD 23
               CXX_EXTENSIONS OFF
               CXX_STANDART_REQUIRED ON)

  target_compile_options(
    my_message
    PRIVATE "-fPIC" ${CXX_FLAGS} "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
            "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>")
endif()

# Shared objects are not linked; loaded dynamically during runtime; DSO there is
# alsp MODULE; which are also shared lib can be loaded dynamically; or runtime
# plugin

add_library(message-shared SHARED $<TARGET_OBJECTS:message-objects>
                                  ${Python_LIBRARIES})

# add_library(message-static STATIC $<TARGET_OBJECTS:message-objects>)

# add_executable(my_message3 main.cpp )

# target_link_libraries(my_message message-static)

# using object file linked to executable

add_executable(my_message2 main.cpp $<TARGET_OBJECTS:message-objects>)
target_include_directories(my_message2 PRIVATE ${PYTHON_INCLUDE_DIRS}
                                               ${Python_LIBRARY_DIRS})
target_link_libraries(my_message2 PRIVATE Eigen3::Eigen ${Python_LIBRARIES}
                                          Boost::filesystem)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(my_message PUBLIC "Is_Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_definitions(my_message PUBLIC "Is_MACOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(my_message PUBLIC "Is_Windows")
endif()

# CMAKE_SIZEOF_VOID_P is used to determine 32 or 64 bit
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_compile_definitions(my_message PUBLIC "IS_64_BIT_ARCH")
else()
  target_compile_definitions(my_message PUBLIC "IS_32_BIT_ARCH")
endif()

target_compile_definitions(
  my_message PUBLIC "ARCHITECTURE= ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# example for executing a Pthon script during build time

# execute_process( COMMAND ${Python_EXECUTABLE} "-c" "print ('Hello Python!')"
# RESULT_VARIABLE _status OUTPUT_VARIABLE _hello_world ERROR_QUIET
# OUTPUT_STRIP_TRAILING_WHITESPACE)

# message(STATUS "RESULT_VARIABLE is: ${_status}") message(STATUS
# "OUTPUT_VARIABLE is: ${_hello_world}")

execute_process(
  COMMAND ${PYTHON_EXECUTABLE} "-c" "import re, numpy;
print(re.compile('/__init__.py.*').sub('',numpy.__file__))"
  RESULT_VARIABLE _numpy_status
  OUTPUT_VARIABLE _numpy_location
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
