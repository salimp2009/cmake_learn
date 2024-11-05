add_library(message_shared SHARED "")
add_library(message::message_shared ALIAS message_shared)

target_sources(message_shared PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Message.cpp)

target_link_libraries(message_shared PRIVATE commonPCH)

# target_precompile_headers(message_shared PRIVATE
# ${PROJECT_SOURCE_DIR}/include/commonPCH.hpp)

target_compile_definitions(
  message_shared
  PUBLIC $<$<BOOL:${UUID_FOUND}>:HAVE_UUID>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  message_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/message>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

target_link_libraries(message_shared
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)

set_target_properties(
  message_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "message"
             DEBUG_POSTFIX "_d"
             # PUBLIC_HEADER
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
             MACOSX_RPATH ON)

# this sets libname_EXPORT macros for visibility for shared libs
include(GenerateExportHeader)
generate_export_header(
  message_shared
  BASE_NAME
  "message"
  EXPORT_MACRO_NAME
  "message_EXPORT"
  EXPORT_FILE_NAME
  "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
  DEPRECATED_MACRO_NAME
  "message_DEPRECATED"
  NO_EXPORT_MACRO_NAME
  "message_NO_EXPORT"
  STATIC_DEFINE
  "message_STATIC_DEFINE"
  NO_DEPRECATED_MACRO_NAME
  "message_NO_DEPRECATED"
  DEFINE_NO_DEPRECATED)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET message_shared ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# if(${ENABLE_LTO})
#   target_enable_lto(TARGET message_shared ENABLE ${ENABLE_LTO})
# endif()

add_library(message_static STATIC "")
add_library(message::message_static ALIAS message_static)

target_sources(message_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Message.cpp)

# target_precompile_headers(message_static REUSE_FROM message_shared)

target_link_libraries(message_static PRIVATE commonPCH)

target_compile_definitions(
  message_static
  PUBLIC message_STATIC_DEFINE $<$<BOOL:${UUID_FOUND}>:HAVE_UUID>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  message_static
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/message>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

target_link_libraries(message_static
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)

set_target_properties(
  message_static
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             # CXX_VISIBILITY_PRESET hidden
             # VISIBILITY_INLINES_HIDDEN YES
             ARCHIVE_OUTPUT_NAME "message"
             DEBUG_POSTFIX "_sd"
             RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET message_static ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET message_static ENABLE ${ENABLE_LTO})
endif()
