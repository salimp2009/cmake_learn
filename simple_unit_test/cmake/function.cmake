function(f mandatory1 mandatory2)
  message("mandatory1=${mandatory1}, mandatory2=${mandatory2}")
  message("ARGC=${ARGC}")
  message("ARGV=${ARGV}")
  message("ARGN=${ARGN}")
  list(APPEND argn "${ARGN}")

  foreach(arg IN LISTS ARGN)
    message("arg= ${arg}")
  endforeach()

  foreach(arg IN LISTS argn)
    message("arg2= ${arg}")
  endforeach()
endfunction()

function(read_semver)
  set(prefix ARG)
  set(options SPLIT DEBUG_INFO)
  set(oneValueArgs OUTPUT_VARIABLE_NAME FILE_NAME)
  set(multiValueArgs MV)
  # Process the arguments passed in
  include(CMakeParseArguments)

  cmake_parse_arguments(${prefix} "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN})
  if(${prefix}_DEBUG_INFO)
    message("arg_debug_info :${${prefix}_DEBUG_INFO}")
    message("arg_split :${${prefix}_SPLIT}")
    message("arg_output_variable :${${prefix}_OUTPUT_VARIABLE_NAME}")
    message("arg_file_name :${${prefix}_FILE_NAME}")
    message("arg_mv :${${prefix}_MV}")
  endif()

  file(READ "${${prefix}_FILE_NAME}" FILE_CONTENT)
  string(STRIP "${FILE_CONTENT}" FILE_CONTENT)
  #
  if(NOT ${prefix}_OUTPUT_VARIABLE_NAME)
    set(${prefix}_OUTPUT_VARIABLE_NAME "VERSION")
    message("Please set OUTPUT_VARIABLE_NAME for read_semver() function")
  endif()

  if(${prefix}_SPLIT)
    message("FILE_CONTENT=${FILE_CONTENT}")

    # replace . with ; from FILE_CONTENTs and save it in SEMVER
    string(REPLACE "." ";" SEMVER_COMPONENTS "${FILE_CONTENT}")
    message("SEMVER_COMPONENTS=${SEMVER_COMPONENTS}")

    list(GET SEMVER_COMPONENTS 0 MAJOR)
    list(GET SEMVER_COMPONENTS 1 MINOR)
    list(GET SEMVER_COMPONENTS 2 PATCH)

    message("MAJOR, MINOR, PATCH = ${MAJOR} ${MINOR} ${PATCH}")

    set(${${prefix}_OUTPUT_VARIABLE_NAME}_MAJOR
        ${MAJOR}
        PARENT_SCOPE)
    set(${${prefix}_OUTPUT_VARIABLE_NAME}_MINOR
        ${MINOR}
        PARENT_SCOPE)
    set(${${prefix}_OUTPUT_VARIABLE_NAME}_PATCH
        ${PATCH}
        PARENT_SCOPE)
  else()
    set(${${prefix}_OUTPUT_VARIABLE_NAME}
        ${FILE_CONTENT}
        PARENT_SCOPE)
  endif()
endfunction()

set(WHATEVER "this is my meesage from function.cmake")
message(
  "in function.cmake: CMAKE_CURRENT_LIST_DIR= ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}"
)
