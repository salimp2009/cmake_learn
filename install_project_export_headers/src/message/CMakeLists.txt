add_library(message_shared SHARED "")

target_sources(message_shared PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Message.cpp)

target_include_directories(
  message_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/message>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

target_compile_definitions(
  message_shared
  PUBLIC $<$<BOOL:${UUID_FOUND}>:HAVE_UUID>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_link_libraries(message_shared
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)

set_target_properties(
  message_shared
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "message2"
             DEBUG_POSTFIX "_d"
             # PUBLIC_HEADER
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
             MACOSX_RPATH ON)

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
  "message_NO_DEPRECATED"
  STATIC_DEFINE
  "message_STATIC_DEFINE"
  NO_DEPRECATED_MACRO_NAME
  "message_NO_DEPRECATED"
  DEFINE_NO_DEPRECATED)

add_library(message_static STATIC "")

target_sources(message_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Message.cpp)

target_compile_definitions(
  message_static
  PUBLIC message_STATIC_DEFINE $<$<BOOL:${UUID_FOUND}>:HAVE_UUID>
  INTERFACE $<INSTALL_INTERFACE:USING_message>)

target_link_libraries(message_static
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)

target_include_directories(
  message_static
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/message>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME})

set_target_properties(
  message_static
  PROPERTIES POSITION_INDEPENDENT_CODE 1
             ARCHIVE_OUTPUT_NAME "message2"
             DEBUG_POSTFIX "_sd"
             RELEASE_POSTFIX "_s"
             # PUBLIC_HEADER
             # "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/messageExport.h"
)

# install( TARGETS message_shared message_static ARCHIVE DESTINATION
# ${INSTALL_LIBDIR}/${PROJECT_NAME} COMPONENT lib RUNTIME DESTINATION
# ${INSTALL_BINDIR} COMPONENT bin LIBRARY DESTINATION
# ${INSTALL_LIBDIR}/${PROJECT_NAME} COMPONENT lib PUBLIC_HEADER DESTINATION
# ${INSTALL_INCLUDEDIR}/${PROJECT_NAME}/ COMPONENT dev)

# install( DIRECTORY ${PROJECT_SOURCE_DIR}/include/
# ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/ DESTINATION
# ${INSTALL_INCLUDEDIR}/${PROJECT_NAME}/ COMPONENT dev PATTERN "*.in" EXCLUDE)
