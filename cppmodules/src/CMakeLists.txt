add_library(Algo STATIC)

target_sources(
  Algo
  PRIVATE algo_impl.cpp
  PUBLIC FILE_SET CXX_MODULES BASE_DIRS ${CMAKE_CURRENT_LIST_DIR} FILES
         algo_interface.cpp)
target_compile_features(Algo PUBLIC cxx_std_23)
# target_compile_options(Algo PRIVATE -save-temps=obj)
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")

target_sources(
  Algo
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}
         FILES ${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/config.hpp)
target_link_libraries(Algo PRIVATE fmt::fmt)

# add_compile_options(#[[ --experimental-modules-support ]] -fmodules-ts)

add_executable(moduleApp main.cpp)
target_compile_features(moduleApp PRIVATE cxx_std_23)
target_link_libraries(moduleApp PRIVATE Algo fmt::fmt)
# target_compile_options(moduleApp PRIVATE -save-temps=obj)
