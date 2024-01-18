add_library(compbase_shared SHARED "")
add_library(message::compbase_shared ALIAS compbase_shared)

target_sources(compbase_shared
               PRIVATE ${CMAKE_CURRENT_LIST_DIR}/compbasics_check.cpp)

target_link_libraries(compbase_shared PRIVATE commonPCH #[[ fmt::fmt ]])

# this is needed when REUSE_FROM used PCH

# target_precompile_headers(corobase_shared  PRIVATE
# ${PROJECT_SOURCE_DIR}/include/commonPCH.hpp)

target_compile_definitions(
  compbase_shared
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  compbase_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/comparison>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  compbase_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "compbase"
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

add_library(compbase STATIC "")
add_library(message::compbase ALIAS compbase)

target_sources(compbase PRIVATE ${CMAKE_CURRENT_LIST_DIR}/compbasics_check.cpp)

# target_precompile_headers(corobase  REUSE_FROM corobase_shared)

target_link_libraries(compbase PRIVATE commonPCH #[[ fmt::fmt ]])

target_compile_definitions(
  compbase
  PUBLIC message_STATIC_DEFINE
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  compbase
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/comparison>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  compbase
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             ARCHIVE_OUTPUT_NAME "compbase"
             SOVERSION ${PROJECT_VERSION_MAJOR}
             DEBUG_POSTFIX "_d"
             # RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER #
             #[[ "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h" ]]
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET compbase_shared ENABLE ${ENABLE_WARNINGS}
                      AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET compbase_shared ENABLE ${ENABLE_LTO})
endif()

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET compbase ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET compbase ENABLE ${ENABLE_LTO})
endif()
