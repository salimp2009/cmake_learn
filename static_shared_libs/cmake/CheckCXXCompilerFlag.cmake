include(CheckCXXSourceCompiles)

macro(CHECK_CXX_COMPILER_FLAG _FLAG _RESULT)
  set(SAFE_CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS}")
  set(CMAKE_REQUIRED_DEFINITIONS "${_FLAG}")
  if(${ARGC} GREATER 2)
    set(TEST_SOURCE "${ARGV2}")
  else()
    set(TEST_SOURCE "int main() { return 0;}")
  endif()
  check_cxx_source_compiles(
    "${TEST_SOURCE}"
    ${_RESULT}
    # Some compilers do not fail with a bad flag
    FAIL_REGEX
    "error: bad value (.*) for .* switch" # GNU
    FAIL_REGEX
    "argument unused during compilation" # clang
    FAIL_REGEX
    "is valid for .* but not for C\\\\+\\\\+" # GNU
    FAIL_REGEX
    "unrecognized .*option" # GNU
    FAIL_REGEX
    "ignored for target" # GNU
    FAIL_REGEX
    "ignoring unknown option" # MSVC
    FAIL_REGEX
    "warning D9002" # MSVC
    FAIL_REGEX
    "[Uu]nknown option" # HP
    FAIL_REGEX
    "[Ww]arning: [Oo]ption" # SunPro
    FAIL_REGEX
    "command option .* is not recognized" # XL
    FAIL_REGEX
    "WARNING: unknown flag:" # Open64
    FAIL_REGEX
    "command line error" # ICC
    FAIL_REGEX
    "command line warning" # ICC
    FAIL_REGEX
    "#10236:" # ICC: File not found
    FAIL_REGEX
    " #10159: " # ICC
    FAIL_REGEX
    " #10353: " # ICC: option '-mfma' ignored, suggest using '-march=core-avx2'
  )
  set(CMAKE_REQUIRED_DEFINITIONS "${SAFE_CMAKE_REQUIRED_DEFINITIONS}")
endmacro(CHECK_CXX_COMPILER_FLAG)
