add_library(Algo STATIC)

target_sources(
  Algo
  PRIVATE algo_impl.cpp
  PUBLIC FILE_SET CXX_MODULES BASE_DIRS ${CMAKE_CURRENT_LIST_DIR} FILES
         algo_interface.cpp)
target_compile_features(Algo PUBLIC cxx_std_26)
# target_compile_options(Algo PRIVATE -save-temps=obj)

target_sources(
  Algo
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}
         FILES ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/config.hpp)
target_link_libraries(Algo PRIVATE fmt::fmt)

# set_target_properties(Algo PROPERTIES CXX_SCAN_FOR_MODULES true)
# add_compile_options(#[[ --experimental-modules-support ]] -fmodules-ts)

add_executable(moduleApp main.cpp)
target_compile_features(moduleApp PRIVATE cxx_std_26)
target_link_libraries(moduleApp PRIVATE Algo fmt::fmt)
# target_compile_options(moduleApp PRIVATE -save-temps=obj)
