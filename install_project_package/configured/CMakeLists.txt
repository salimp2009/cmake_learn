# set(GIT_HASH2 "unknown")

# # if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION") file(READ #
# "${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION" PROGRAM_VERSION) # this is for #
# trimming whitespace string(STRIP "${PROGRAM_VERSION}" PROGRAM_VERSION) else()
# # message(FATAL_ERROR "File ${CMAKE_CURRENT_SOURCE_DIR}/include/VERSION not #
# found") endif()

# # this only work at config time or if any change to cmake is done if only
# source # code changes the git status is not refreshed

# find_package(Git QUIET) if(GIT_FOUND) execute_process( COMMAND
# ${GIT_EXECUTABLE} log -1 --pretty=format:%h OUTPUT_VARIABLE GIT_HASH2
# OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

# execute_process( COMMAND ${GIT_EXECUTABLE} describe --abbrev=7 --long --always
# --dirty --tags OUTPUT_VARIABLE GIT_STATUS2 OUTPUT_STRIP_TRAILING_WHITESPACE
# ERROR_QUIET) endif()

# message("Git hash2 is ${GIT_HASH2}") message("Git status2 is ${GIT_STATUS2}")

# configure_file( "config.hpp.in"
# "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/config.hpp" ESCAPE_QUOTES)

# generating git_hash and status & will be updated every build

# add_custom_command( OUTPUT
# ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/version.hpp COMMAND ${CMAKE_COMMAND}
# -D TARGET_DIR=${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR} -D
# PROGRAM_VERSION=${PROJECT_VERSION} -D
# PROGRAM_VERSION_MAJOR=${PROJECT_VERSION_MAJOR} -D
# PROGRAM_VERSION_MINOR=${PROJECT_VERSION_MINOR} -D
# PROGRAM_VERSION_PATCH=${PROJECT_VERSION_PATCH} -D
# PROGRAM_VERSION_TWEAK=${PROJECT_VERSION_TWEAK} -D PROGRAM_NAME=${PROJECT_NAME}
# -P ${PROJECT_SOURCE_DIR}/cmake/git-hash.cmake WORKING_DIRECTORY
# ${CMAKE_CURRENT_LIST_DIR})

# add_custom_target(get_git_hash ALL DEPENDS
# ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/version.hpp)
