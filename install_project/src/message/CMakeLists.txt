add_library(message_shared SHARED "")

target_sources(
  message_shared PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Message.cpp
  #[[ PUBLIC ${PROJECT_SOURCE_DIR}/include/message/Message.hpp ]]
)

target_include_directories(
  message_shared
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/message>
         # $<INSTALL_INTERFACE:include/${CMAKE_PROJECT_NAME}/sort>)
         $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/message>)
# $<INSTALL_INTERFACE:${sorted_INCLUDE_DIR}/include/sort>)

target_compile_definitions(message_shared
                           PUBLIC $<$<BOOL:${UUID_FOUND}>:HAVE_UUID>)

target_link_libraries(message_shared
                      PUBLIC $<$<BOOL:${UUID_FOUND}>:PkgConfig::UUID>)

set_target_properties(
  message_shared
  PROPERTIES #[[ CXX_VISIBILITY_PRESET hidden ]]
             # VISIBILITY_INLINES_HIDDEN YES
             POSITION_INDEPENDENT_CODE 1
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "message"
             DEBUG_POSTFIX "_d"
             # PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/message/Message.hpp"
             MACOSX_RPATH ON
             WINDOWS_EXPORT_ALL_SYMBOLS ON)

install(
  TARGETS message_shared
  ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
  RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
  LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
  PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDEDIR}/message COMPONENT dev)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include
            # TYPE INCLUDE
  DESTINATION ${INSTALL_INCLUDEDIR}/message
  COMPONENT dev
  PATTERN "*.in" EXCLUDE)
