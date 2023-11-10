macro(generate_dep_graph)
  # Check if the 'dot' command is available
  find_program(DOT_EXECUTABLE dot)
  if(NOT DOT_EXECUTABLE)
    message(
      FATAL_ERROR
        "Graphviz 'dot' command not found. Make sure Graphviz is installed.")
  endif()

  set(DOT_FILE "dep_graph.dot")
  set(PNG_FILE "${CMAKE_SOURCE_DIR}/docs/dep_graph.png")

  add_custom_target(
    dep_graph
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${PNG_FILE}
    COMMENT "Creates a new dependency graph for the documentation"
    VERBATIM)

  add_custom_command(
    OUTPUT ${PNG_FILE}
    COMMAND ${DOT_EXECUTABLE} -T png ${DOT_FILE} -o ${PNG_FILE}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${DOT_FILE}
    COMMENT "Creates a new dependency graph as png")

  add_custom_command(
    OUTPUT ${DOT_FILE}
    COMMAND ${CMAKE_COMMAND} --graphviz=${DOT_FILE} "."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    # DEPENDS ${PROJECT_NAME}
    COMMENT "Creates a new dependency graph")

endmacro()
