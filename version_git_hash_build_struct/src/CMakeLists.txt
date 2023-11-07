add_executable(record_cppversion example.cpp)

target_include_directories(record_cppversion
                           PRIVATE ${PROJECT_BINARY_DIR}/generated)

# make sure version.hpp generated before we build the executable
add_dependencies(record_cppversion get_git_hash)
