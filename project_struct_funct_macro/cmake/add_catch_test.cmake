set(num_macro_calls
    0
    PARENT_SCOPE)

macro(add_catch_test _name _cost)
  math(EXPR num_macro_calls "${num_macro_calls}+1")
  message(STATUS "add_catch_test called with ${ARGC} arguments: ${ARGV}")

  set(_argn "${ARGN}")
  if(_argn)
    message(
      STATUS "oops - macro received argument(s) we did not expect: ${ARGN}")
  endif()

  add_test(
    NAME ${_name}
    COMMAND $<TARGET_FILE:cpp_test> [${_name}] --success --out
            ${PROJECT_BINARY_DIR}/tests/${_name}.log --durations yes
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  set_tests_properties(${_name} PROPERTIES COST ${_cost})
endmacro()
