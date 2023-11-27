set(GIT_HASH2 "unknown")

# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION") file(READ
# "${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION" PROGRAM_VERSION) # this is for
# trimming whitespace string(STRIP "${PROGRAM_VERSION}" PROGRAM_VERSION) else()
# message(FATAL_ERROR "File ${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION not
# found") endif()
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
    OUTPUT_VARIABLE GIT_HASH2
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --abbrev=7 --long --always --dirty --tags
    OUTPUT_VARIABLE GIT_STATUS2
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
endif()

message(STATUS "Git hash2 is ${GIT_HASH2}")

add_custom_target(
  git_status
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS ${GIT_STATUS2}
  COMMENT "git status check"
  VERBATIM)

configure_file(
  "config.hpp.in" "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/config.hpp"
  ESCAPE_QUOTES)

# add_dependencies(git_status hello_world_wDSO2)
