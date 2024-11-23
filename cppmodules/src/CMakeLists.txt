add_library(Algo STATIC)
target_sources(Algo
  PRIVATE
  algo_impl.cpp
  PUBLIC
  FILE_SET CXX_MODULES
  FILES
  algo_interface.cpp
)
target_compile_features(Algo PUBLIC cxx_std_23)

# add_compile_options(-fmodules) 

add_executable(moduleApp main.cpp)
target_compile_features(moduleApp PRIVATE cxx_std_23)
target_link_libraries(moduleApp PRIVATE Algo fmt::fmt)
