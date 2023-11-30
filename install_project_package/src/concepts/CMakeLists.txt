add_library(concepts STATIC "")
add_library(message::concepts ALIAS concepts)

target_sources(concepts PRIVATE ${CMAKE_CURRENT_LIST_DIR}/conceptbasics.cpp)

# target_precompile_headers(concepts REUSE_FROM message_shared)

target_link_libraries(concepts PRIVATE commonPCH)

target_compile_definitions(
  concepts
  PUBLIC message_STATIC_DEFINE
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  concepts
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/concepts>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  concepts
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             ARCHIVE_OUTPUT_NAME "concepts"
             DEBUG_POSTFIX "_sd"
             RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET concepts ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET concepts ENABLE ${ENABLE_LTO})
endif()
