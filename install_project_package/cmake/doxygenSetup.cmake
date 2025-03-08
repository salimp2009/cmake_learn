function(generate_doxygen input output)
  # check if doxygen is available
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    add_custom_target(
      doxygen
      COMMAND false
      COMMENT "Doxygen was not found!")
    return()
  endif()

  # download a modern style for the doxygen documentation
  include(FetchContent)
  FetchContent_Declare(
    doxygen-awesome-css
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG v2.2.1)
  FetchContent_MakeAvailable(doxygen-awesome-css)

  # set doxygen options
  set(DOXYGEN_HTML_EXTRA_STYLESHEET
      "${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css")

  set(DOXYGEN_OUTPUT_DIRECTORY "${output}")
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_TREEVIEW YES)

  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_CLASS_DIAGRAMS YES)
  set(DOXYGEN_HIDE_UNDOC_RELATIONS NO)
  set(DOXYGEN_HAVE_DOT YES)
  set(DOXYGEN_CLASS_GRAPH YES)
  set(DOXYGEN_COLLABORATION_GRAPH YES)
  set(DOXYGEN_UML_LOOK YES)
  set(DOXYGEN_TEMPLATE_RELATIONS YES)
  set(DOXYGEN_DOT_TRANSPARENT YES)
  set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  # set(DOXYGEN_PROJECT_LOGO "${PROJECT_SOURCE_DIR}/res/logo.png")
  # set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/Readme.md")

  # base for generating a documentation pdf file
  set(DOXYGEN_GENERATE_LATEX YES)
  set(DOXYGEN_USE_PDFLATEX YES)
  set(DOXYGEN_PDF_HYPERLINKS YES)

  doxygen_add_docs(
    doxygen "${input}"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Generate Doxygen Documentation")
endfunction()
