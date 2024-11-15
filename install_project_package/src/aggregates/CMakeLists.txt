add_library(aggregbase_shared SHARED "")
add_library(message::aggregbase_shared ALIAS aggregbase_shared)

target_sources(aggregbase_shared
               PRIVATE ${CMAKE_CURRENT_LIST_DIR}/aggregbasics_check.cpp)

target_link_libraries(aggregbase_shared PRIVATE commonPCH #[[ fmt::fmt ]])

# this is needed when REUSE_FROM used PCH

# target_precompile_headers(corobase_shared  PRIVATE
# ${PROJECT_SOURCE_DIR}/include/commonPCH.hpp)

target_compile_definitions(
  aggregbase_shared
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  aggregbase_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/aggregates>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  aggregbase_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "aggregbase"
             DEBUG_POSTFIX "_d" #
             # PUBLIC_HEADER #
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
             MACOSX_RPATH ON)

# include(GenerateExportHeader) generate_export_header( corobase_shared
# BASE_NAME "coro" EXPORT_MACRO_NAME "coro_EXPORT" EXPORT_FILE_NAME
# "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/corobaseExport.h"
# DEPRECATED_MACRO_NAME "coro_DEPRECATED" NO_EXPORT_MACRO_NAME "coro_NO_EXPORT"
# STATIC_DEFINE "coro_STATIC_DEFINE" NO_DEPRECATED_MACRO_NAME
# "coro_NO_DEPRECATED" DEFINE_NO_DEPRECATED)

add_library(aggregbase STATIC "")
add_library(message::aggregbase ALIAS aggregbase)

target_sources(aggregbase
               PRIVATE ${CMAKE_CURRENT_LIST_DIR}/aggregbasics_check.cpp)

# target_precompile_headers(corobase  REUSE_FROM corobase_shared)

target_link_libraries(aggregbase PRIVATE commonPCH #[[ fmt::fmt ]])

target_compile_definitions(
  aggregbase
  PUBLIC message_STATIC_DEFINE
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  aggregbase
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/aggregates>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  aggregbase
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             ARCHIVE_OUTPUT_NAME "aggregbase"
             SOVERSION ${PROJECT_VERSION_MAJOR}
             DEBUG_POSTFIX "_d"
             # RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER #
             #[[ "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h" ]]
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET aggregbase_shared ENABLE ${ENABLE_WARNINGS}
                      AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# if(${ENABLE_LTO})
#   target_enable_lto(TARGET aggregbase_shared ENABLE ${ENABLE_LTO})
# endif()

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET aggregbase ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET aggregbase ENABLE ${ENABLE_LTO})
endif()
