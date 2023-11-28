# recording git_hash during config time
set(GIT_HASH "unknown")

# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION") file(READ
# "${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION" PROGRAM_VERSION) # this is for
# trimming whitespace string(STRIP "${PROGRAM_VERSION}" PROGRAM_VERSION) else()
# message(FATAL_ERROR "File ${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION not
# found") endif()
find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --abbrev=7 --long --always --dirty --tags
    OUTPUT_VARIABLE GIT_STATUS
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
endif()

message(STATUS "Git hash is ${GIT_HASH}")

# generate version.hpp based on version.hpp.in
configure_file(version.hpp.in ${TARGET_DIR}/version.hpp @ONLY)
