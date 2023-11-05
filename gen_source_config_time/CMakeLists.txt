cmake_minimum_required(VERSION 3.21)

project(generatesource1 LANGUAGES Fortran C)

# set(CMAKE_CXX_STANDARD 23) set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
  COMMAND whoami
  TIMEOUT 1
  OUTPUT_VARIABLE _user_name
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# # host info cmake_host_system_information(RESULT _host_name QUERY HOSTNAME) #
# query full qualified domain name cmake_host_system_information(RESULT _fqdn
# QUERY FQDN)

# host name information
cmake_host_system_information(RESULT _host_name QUERY HOSTNAME)
cmake_host_system_information(RESULT _fqdn QUERY FQDN)

# processor info
cmake_host_system_information(RESULT _processor_name QUERY PROCESSOR_NAME)
cmake_host_system_information(RESULT _processor_description
                              QUERY PROCESSOR_DESCRIPTION)

# os information
cmake_host_system_information(RESULT _os_name QUERY OS_NAME)
cmake_host_system_information(RESULT _os_release QUERY OS_RELEASE)
cmake_host_system_information(RESULT _os_version QUERY OS_VERSION)
cmake_host_system_information(RESULT _os_platform QUERY OS_PLATFORM)

string(TIMESTAMP _configuration_time "%Y-%m-%d %H:%M:%S [UTC]" UTC)

configure_file(print_info.c.in print_info.c @ONLY)

add_executable(fortran_print "")
target_sources(fortran_print PRIVATE example.f90
                                     ${CMAKE_CURRENT_BINARY_DIR}/print_info.c)
