include(GNUInstallDirs)

macro(set_build_dir)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

  # install subdirectories ; CMAKE_INSTALL_PREFIX will be prepended
  set(INSTALL_LIBDIR
      ${CMAKE_INSTALL_LIBDIR}
      CACHE PATH "Install directory for libraries")
  set(INSTALL_BINDIR
      ${CMAKE_INSTALL_BINDIR}
      CACHE PATH "Install directory for binaries")
  set(INSTALL_INCLUDEDIR
      ${CMAKE_INSTALL_INCLUDEDIR}
      CACHE PATH "Install directory for header files")

  # install subdirectories for cmake files(generated by cmake)
  if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKEDIR CMake)
  else()
    set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
  endif()

  set(INSTALL_CMAKEDIR
      ${DEF_INSTALL_CMAKEDIR}
      CACHE PATH "Installation directory for CMake files")

  # Report to user install directories
  foreach(p LIB BIN INCLUDE CMAKE)
    file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path)
    message(STATUS "Installing ${p} components to ${_path}")
    unset(_path)
  endforeach()

endmacro()
