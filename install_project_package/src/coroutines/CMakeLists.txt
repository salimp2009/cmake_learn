add_library(corobase_shared SHARED "")
add_library(message::corobase_shared ALIAS corobase_shared)

target_sources(corobase_shared
               PRIVATE ${CMAKE_CURRENT_LIST_DIR}/corobasics_check.cpp)

target_link_libraries(corobase_shared PRIVATE commonPCH)

# this is needed when REUSE_FROM used PCH

# target_precompile_headers(corobase_shared  PRIVATE
# ${PROJECT_SOURCE_DIR}/include/commonPCH.hpp)

target_compile_definitions(
  corobase_shared
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  corobase_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/coroutines>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  corobase_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "corobase"
             DEBUG_POSTFIX "_d" #
             # PUBLIC_HEADER #
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
             MACOSX_RPATH ON)

# include(GenerateExportHeader) generate_export_header( concepts_shared
# BASE_NAME "concepts" EXPORT_MACRO_NAME "concepts_EXPORT" EXPORT_FILE_NAME
# "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/conceptsExport.h"
# DEPRECATED_MACRO_NAME "concepts_DEPRECATED" NO_EXPORT_MACRO_NAME
# "concepts_NO_EXPORT" STATIC_DEFINE "concepts_STATIC_DEFINE"
# NO_DEPRECATED_MACRO_NAME "concepts_NO_DEPRECATED" DEFINE_NO_DEPRECATED)

add_library(corobase STATIC "")
add_library(message::corobase ALIAS corobase)

target_sources(corobase PRIVATE ${CMAKE_CURRENT_LIST_DIR}/corobasics_check.cpp)

# target_precompile_headers(corobase  REUSE_FROM corobase_shared)

target_link_libraries(corobase PRIVATE commonPCH)

target_compile_definitions(
  corobase
  PUBLIC message_STATIC_DEFINE
  PRIVATE $<$<CONFIG:Debug>:DEBUG>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  corobase
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/coroutines>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  corobase
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             ARCHIVE_OUTPUT_NAME "corobase"
             SOVERSION ${PROJECT_VERSION_MAJOR}
             DEBUG_POSTFIX "_d"
             # RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER #
             #[[ "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h" ]]
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET corobase_shared ENABLE ${ENABLE_WARNINGS}
                      AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET corobase_shared ENABLE ${ENABLE_LTO})
endif()

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET corobase ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET corobase ENABLE ${ENABLE_LTO})
endif()