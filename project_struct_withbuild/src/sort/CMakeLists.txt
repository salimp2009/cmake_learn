add_library(sort STATIC sort.cpp sum_vector.cpp)
add_library(sorted::sort ALIAS sort)

include(GNUInstallDirs)
target_include_directories(
  sort
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/sort>
         # $<INSTALL_INTERFACE:include/${CMAKE_PROJECT_NAME}/sort>)
         $<INSTALL_INTERFACE:include/${CMAKE_PROJECT_NAME}/include/sort>)
# $<INSTALL_INTERFACE:${sorted_INCLUDE_DIR}/include/sort>)

target_compile_features(sort PUBLIC cxx_std_23)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET sort ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET sort ENABLE ${ENABLE_LTO})
endif()

# trial from youtube cppcon target_include_directories( sort PUBLIC
# $<BUILD_INTERFACE:${sort_BINARY_DIR}/${CMAKE_SOURCE_DIR}/include/sort>
# $<BUILD_INTERFACE:${sort_SOURCE_DIR}/${CMAKE_SOURCE_DIR}/include/sort>
# $<INSTALL_INTERFACE:include/sort>)
