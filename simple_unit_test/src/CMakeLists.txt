set(WHATEVER2
    "this message is from subdirectory ./src"
    PARENT_SCOPE)

add_subdirectory(sort)
message("CMAKE_CURRENT_SOURCE_DIR =${CMAKE_CURRENT_SOURCE_DIR}")
