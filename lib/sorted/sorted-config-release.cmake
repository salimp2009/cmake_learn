#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sort" for configuration "Release"
set_property(TARGET sort APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sort PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libsort.a"
  )

list(APPEND _cmake_import_check_targets sort )
list(APPEND _cmake_import_check_files_for_sort "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libsort.a" )

# Import target "print" for configuration "Release"
set_property(TARGET print APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(print PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libprint.a"
  )

list(APPEND _cmake_import_check_targets print )
list(APPEND _cmake_import_check_files_for_print "/home/salim/repos/cpp_sandbox/cmake_learn/lib/sorted/libprint.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
