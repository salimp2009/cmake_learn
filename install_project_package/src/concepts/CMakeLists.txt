add_library(concepts_shared SHARED "")
add_library(message::concepts_shared ALIAS concepts_shared)

target_sources(concepts_shared
               PRIVATE ${CMAKE_CURRENT_LIST_DIR}/conceptbasics.cpp)

target_link_libraries(concepts_shared PRIVATE commonPCH)

# this is needed when REUSE_FROM used PCH

# target_precompile_headers(concepts_shared  PRIVATE
# ${PROJECT_SOURCE_DIR}/include/commonPCH.hpp)

target_compile_definitions(concepts_shared
                           INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_include_directories(
  concepts_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/concepts>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

set_target_properties(
  concepts_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "concepts"
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

add_library(concepts STATIC "")
add_library(message::concepts ALIAS concepts)

target_sources(concepts PRIVATE ${CMAKE_CURRENT_LIST_DIR}/conceptbasics.cpp)

# target_precompile_headers(concepts REUSE_FROM concepts_shared)

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
             SOVERSION ${PROJECT_VERSION_MAJOR}
             DEBUG_POSTFIX "_d"
             # RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER #
             #[[ "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h" ]]
)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET concepts_shared ENABLE ${ENABLE_WARNINGS}
                      AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET concepts_shared ENABLE ${ENABLE_LTO})
endif()

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET concepts ENABLE ${ENABLE_WARNINGS} AS_ERRORS
                      ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
  target_enable_lto(TARGET concepts ENABLE ${ENABLE_LTO})
endif()
