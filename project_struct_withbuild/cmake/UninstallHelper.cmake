if(NOT EXISTS "${CMAKE_BINARY_DIR}/install_manifest.txt")
  message(
    FATAL_ERROR
      "Cannot find install manifest: ${CMAKE_BINARY_DIR}/install_manifest.txt")
endif()

file(STRINGS "${CMAKE_BINARY_DIR}/install_manifest.txt" files)
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    file(REMOVE $ENV{DESTDIR}${file})
  else()
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif()
endforeach()
