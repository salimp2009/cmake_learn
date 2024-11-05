add_library(formatbase_shared SHARED "")
add_library(message::formatbase_shared ALIAS formatbase_shared)

target_sources(
  formatbase_shared
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/formatbasics_check.cpp
          ${CMAKE_CURRENT_LIST_DIR}/stockindex.cpp
          ${CMAKE_CURRENT_LIST_DIR}/formatlog.cpp)

target_link_libraries(rangebase_shared PRIVATE commonPCH #[[ fmt::fmt ]])

# this is needed when REUSE_FROM used PCH

# target_precompile_headers(corobase_shared  PRIVATE
# ${PROJECT_SOURCE_DIR}/include/commonPCH.hpp)

target_compile_definitions(
  formatbase_shared
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  formatbase_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/format>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  formatbase_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "formatbase"
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

add_library(formatbase STATIC "")
add_library(message::formatbase ALIAS formatbase)

target_sources(
  formatbase
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/formatbasics_check.cpp
          ${CMAKE_CURRENT_LIST_DIR}/stockindex.cpp
          ${CMAKE_CURRENT_LIST_DIR}/formatlog.cpp)

# target_precompile_headers(corobase  REUSE_FROM corobase_shared)

target_link_libraries(formatbase PRIVATE commonPCH #[[ fmt::fmt ]])

target_compile_definitions(
  formatbase
  PUBLIC message_STATIC_DEFINE
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  formatbase
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/format>
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/fmt>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  formatbase
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             ARCHIVE_OUTPUT_NAME "formatbase"
             SOVERSION ${PROJECT_VERSION_MAJOR}
             DEBUG_POSTFIX "_d"
             # RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER #
             #[[ "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h" ]]
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET formatbase_shared ENABLE ${ENABLE_WARNINGS}
                      AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# enabling Lto causes ASAN to give error after gcc update to 13.2.1-5 it was
# working before
# if(${ENABLE_LTO})
#   target_enable_lto(TARGET formatbase_shared ENABLE ${ENABLE_LTO})
# endif()

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET formatbase ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET formatbase ENABLE ${ENABLE_LTO})
endif()
