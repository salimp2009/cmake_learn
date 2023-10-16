add_library(print STATIC print.cpp)
add_library(sorted::print ALIAS print)

target_include_directories(print PUBLIC "${CMAKE_SOURCE_DIR}/include/print")
target_compile_features(print PUBLIC cxx_std_23)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET print ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET print ENABLE ${ENABLE_LTO})
endif()
