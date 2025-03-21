macro(standartProjectsettings)
  # Enhance error reporting and compiler messages
  if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    if(WIN32)
      # On Windows cuda nvcc uses cl and not clang
      add_compile_options($<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics>
                          $<$<COMPILE_LANGUAGE:CXX>:-fcolor-diagnostics>)
    else()
      add_compile_options(-fcolor-diagnostics )
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(WIN32)
      # On Windows cuda nvcc uses cl and not gcc
      add_compile_options($<$<COMPILE_LANGUAGE:C>:-fdiagnostics-color=always>
                          $<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color=always>)
    else()
      add_compile_options(-fdiagnostics-color=always )
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION GREATER 1900)
    add_compile_options(/diagnostics:column)
  else()
    message(
      STATUS
        "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler."
    )
  endif()
endmacro()
