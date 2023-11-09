set(num_macro_calls
    0
    PARENT_SCOPE)

# list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake") include(colors)
# define_colors()

# the above color cmake and module_path variables are defined at top level so
# all other modules can use it

macro(add_catch_test _name _cost)
  math(EXPR num_macro_calls "${num_macro_calls}+1")
  message(
    STATUS
      "${Green}add_catch_test called with  ${ARGC} arguments: ${ARGV}${ColourReset}"
  )

  set(_argn "${ARGN}")
  if(_argn)
    message(
      STATUS
        "${Yellow}oops - macro received argument(s) we did not expect:${ARGN}${ColourReset}"
    )
  endif()

  add_test(
    NAME ${_name}
    COMMAND $<TARGET_FILE:cpp_test> [${_name}] --success --out
            ${PROJECT_BINARY_DIR}/tests/${_name}.log --durations yes
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  set_tests_properties(${_name} PROPERTIES COST ${_cost})
endmacro()
