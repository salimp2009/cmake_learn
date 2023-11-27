macro(generate_git_hash)
  add_custom_target(
    git_status
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${GIT_HASH2}
    COMMENT "git status check"
    VERBATIM)

  add_custom_command(
    OUTPUT GIT_HASH2
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${GIT_STATUS2}
    COMMENT "creating GIT_HASH2")

  add_custom_command(
    OUTPUT GIT_STATUS2
    COMMAND ${GIT_EXECUTABLE} describe --abbrev=7 --long --always --dirty --tags
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${GIT_EXECUTABLE}
    COMMENT "Creating GIT_STATUS2")

endmacro()
