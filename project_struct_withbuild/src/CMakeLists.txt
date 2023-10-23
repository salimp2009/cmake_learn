add_subdirectory(sort)
add_subdirectory(print)

add_executable(sortprint main.cpp)
target_link_libraries(sortprint PRIVATE sorted::print sorted::sort)
# target_link_libraries(sortprint PRIVATE print sort)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET sortprint ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET sortprint ENABLE ${ENABLE_LTO})
endif()
