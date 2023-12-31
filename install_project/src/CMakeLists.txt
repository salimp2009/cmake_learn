# Search for pkg-config and UUID

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_search_module(UUID uuid IMPORTED_TARGET)
  if(TARGET PkgConfig::UUID)
    message(STATUS "Found libuuid")
    set(UUID_FOUND TRUE)
  endif()
endif()

add_subdirectory(message)

add_executable(hello-world_wDSO hello-world.cpp)
target_link_libraries(hello-world_wDSO PUBLIC message_shared)

# prepare RPATH

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
  hello-world_wDSO
  PROPERTIES MACOSX_RPATH ON
             SKIP_BUILD_RPATH OFF
             BUILD_WITH_INSTALL_RPATH OFF
             INSTALL_RPATH "${message_RPATH}"
             INSTALL_RPATH_USE_LINK_PATH ON)

install(
  TARGETS hello-world_wDSO
  ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
  RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
  LIBRARY
    DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
    #[[ PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDEDIR}/message COMPONENT dev ]]
)
