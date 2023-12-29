# Search for pkg-config and UUID

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_search_module(UUID uuid IMPORTED_TARGET)
  if(TARGET PkgConfig::UUID)
    message(STATUS "Found libuuid")
    set(UUID_FOUND TRUE)
  endif()
endif()

add_library(commonPCH INTERFACE)
target_precompile_headers(commonPCH INTERFACE [["commonPCH.hpp"]])

target_include_directories(
  commonPCH
  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/${PROJECT_NAME}>)

add_subdirectory(message)
add_subdirectory(concepts)
add_subdirectory(coroutines)
add_subdirectory(ranges)

add_executable(hello_world_wDSO2 hello-world.cpp)
target_link_libraries(
  hello_world_wDSO2
  PUBLIC message::message_shared message::concepts_shared
         message::corobase_shared message::rangebase_shared fmt::fmt)

file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR}
     ${CMAKE_INSTALL_PREFIX})
if(APPLE)
  set(_rpath "@loader_path/${_rel}")
else()
  set(_rpath "\$ORIGIN/${_rel}")
endif()
file(TO_NATIVE_PATH "${_rpath}/${INSTALL_LIBDIR}" message_RPATH)

message("INSTALL_INCLUDEDIR=${INSTALL_INCLUDEDIR}")
message("message_RPATH=${message_RPATH}")

set_target_properties(
  hello_world_wDSO2
  PROPERTIES MACOSX_RPATH ON
             SKIP_BUILD_RPATH OFF
             BUILD_WITH_INSTALL_RPATH OFF
             INSTALL_RPATH "${message_RPATH}"
             INSTALL_RPATH_USE_LINK_PATH ON)

add_executable(hello_world_wAR2 hello-world.cpp)
target_link_libraries(
  hello_world_wAR2 PUBLIC message::message_static message::concepts
                          message::corobase message::rangebase fmt::fmt)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
            ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/
  DESTINATION ${INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  COMPONENT dev
  PATTERN "*.in" EXCLUDE)

install(
  TARGETS hello_world_wDSO2
          hello_world_wAR2
          message_shared
          message_static
          concepts
          concepts_shared
          corobase
          corobase_shared
          rangebase
          rangebase_shared
          commonPCH
  EXPORT messageTargets
  ARCHIVE DESTINATION ${INSTALL_LIBDIR}/${PROJECT_NAME} COMPONENT lib
  RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
  LIBRARY DESTINATION ${INSTALL_LIBDIR}/${PROJECT_NAME} COMPONENT lib
  PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
                COMPONENT dev)

install(
  EXPORT messageTargets
  NAMESPACE "message::"
  DESTINATION ${INSTALL_CMAKEDIR}
  COMPONENT dev)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/messageConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/messageConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/messageConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CMAKEDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/messageConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/messageConfigVersion.cmake
        DESTINATION ${INSTALL_CMAKEDIR})
