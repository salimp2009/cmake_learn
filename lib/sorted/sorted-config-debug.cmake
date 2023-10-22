#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sorted::sort" for configuration "Debug"
set_property(TARGET sorted::sort APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(sorted::sort PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libsort.a"
  )

list(APPEND _cmake_import_check_targets sorted::sort )
list(APPEND _cmake_import_check_files_for_sorted::sort "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libsort.a" )

# Import target "sorted::print" for configuration "Debug"
set_property(TARGET sorted::print APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(sorted::print PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libprint.a"
  )

list(APPEND _cmake_import_check_targets sorted::print )
list(APPEND _cmake_import_check_files_for_sorted::print "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libprint.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
