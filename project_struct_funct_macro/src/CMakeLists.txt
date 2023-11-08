# Automatically add the current source and build directories to the
# INTERFACE_INCLUDE_DIRECTORIES target property.

# set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

add_library(sum_integers STATIC sum_integers.cpp)
target_include_directories(sum_integers PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(sum_up main.cpp)
target_link_libraries(sum_up PRIVATE sum_integers)
