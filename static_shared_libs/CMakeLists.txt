cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-03 LANGUAGES CXX)

# objects can be used later to create static or shared objects
# add_library(message-objects OBJECT message.hpp message.cpp)

option(USE_LIBRARY "Set the value on for static linking" OFF)
message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

set(BUILD_SHARED_LIBS OFF)
list(APPEND sources message.hpp message.cpp)

# set_target_properties(message-objects PROPERTIES POSITION_INDEPENDENT_CODE 1)

if(USE_LIBRARY)
  # add_library will create static lib
  add_library(message STATIC ${sources})
  add_executable(my_message main.cpp)
  target_link_libraries(my_message PUBLIC message)
else()
  add_executable(my_message main.cpp ${sources})
endif()

# Shared objects are not linked; loaded dynamically during runtime; DSO there is
# alsp MODULE; which are also shared lib can be loaded dynamically; or runtime
# plugin add_library(message-shared SHARED $<TARGET_OBJECTS:message-objects>)
# add_library(message-static STATIC $<TARGET_OBJECTS:message-objects>)

# add_executable(my_message main.cpp)

# target_link_libraries(my_message message-static)

# using object file linked to executable

# add_executable(my_message main.cpp $<TARGET_OBJECTS:message-objects>)
