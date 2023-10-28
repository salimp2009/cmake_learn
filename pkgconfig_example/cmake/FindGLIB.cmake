# Copyright (C) 2012 Raphael Kubo da Costa <rakuco@webkit.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met: 1.
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer. 2.  Redistributions in binary
# form must reproduce the above copyright notice, this list of conditions and
# the following disclaimer in the documentation and/or other materials provided
# with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND ITS CONTRIBUTORS ``AS
# IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR ITS CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

# * Try to find Glib and its components (gio, gobject etc) Once done, this will
#   define
#
# GLIB_FOUND - system has Glib GLIB_INCLUDE_DIRS - the Glib include directories
# GLIB_LIBRARIES - link these to use Glib

find_library(GLIB_LIBRARY_PATH glib-2.0)

find_path(
  GLIB_INCLUDE_PATH glib.h
  HINTS /usr/include/ /usr/local/include/
  PATH_SUFFIXES glib-2.0)

find_path(GLIBCONFIG_INCLUDE_PATH glibconfig.h
          HINTS /usr/lib64/glib-2.0/include/)

# Version detection
if(EXISTS "${GLIBCONFIG_INCLUDE_PATH}/glibconfig.h")
  file(READ "${GLIBCONFIG_INCLUDE_PATH}/glibconfig.h" GLIBCONFIG_H_CONTENTS)
  string(REGEX MATCH "#define GLIB_MAJOR_VERSION ([0-9]+)" _dummy
               "${GLIBCONFIG_H_CONTENTS}")
  set(GLIB_VERSION_MAJOR "${CMAKE_MATCH_1}")
  string(REGEX MATCH "#define GLIB_MINOR_VERSION ([0-9]+)" _dummy
               "${GLIBCONFIG_H_CONTENTS}")
  set(GLIB_VERSION_MINOR "${CMAKE_MATCH_1}")
  string(REGEX MATCH "#define GLIB_MICRO_VERSION ([0-9]+)" _dummy
               "${GLIBCONFIG_H_CONTENTS}")
  set(GLIB_VERSION_MICRO "${CMAKE_MATCH_1}")
  set(GLIB_VERSION
      "${GLIB_VERSION_MAJOR}.${GLIB_VERSION_MINOR}.${GLIB_VERSION_MICRO}")
endif()

# Additional Glib components.  We only look for libraries, as not all of them
# have corresponding headers and all headers are installed alongside the main
# glib ones.
foreach(_component ${GLIB_FIND_COMPONENTS})
  if(${_component} STREQUAL "gio")
    find_library(
      GLIB_GIO_LIBRARIES
      NAMES gio-2.0
      HINTS ${_GLIB_LIBRARY_DIR})
    set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS} GLIB_GIO_LIBRARIES)
  elseif(${_component} STREQUAL "gobject")
    find_library(
      GLIB_GOBJECT_LIBRARIES
      NAMES gobject-2.0
      HINTS ${_GLIB_LIBRARY_DIR})
    set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS}
                                 GLIB_GOBJECT_LIBRARIES)
  elseif(${_component} STREQUAL "gmodule")
    find_library(
      GLIB_GMODULE_LIBRARIES
      NAMES gmodule-2.0
      HINTS ${_GLIB_LIBRARY_DIR})
    set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS}
                                 GLIB_GMODULE_LIBRARIES)
  elseif(${_component} STREQUAL "gthread")
    find_library(
      GLIB_GTHREAD_LIBRARIES
      NAMES gthread-2.0
      HINTS ${_GLIB_LIBRARY_DIR})
    set(ADDITIONAL_REQUIRED_VARS ${ADDITIONAL_REQUIRED_VARS}
                                 GLIB_GTHREAD_LIBRARIES)
  elseif(${_component} STREQUAL "gio-unix")
    # gio-unix is compiled as part of the gio library, but the include paths are
    # separate from the shared glib ones. Since this is currently only used by
    # WebKitGTK we don't go to extraordinary measures beyond pkg-config.
    pkg_check_modules(GIO_UNIX QUIET gio-unix-2.0)
  endif()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  GLIB
  DEFAULT_MSG
  GLIB_LIBRARY_PATH
  GLIB_INCLUDE_PATH
  GLIBCONFIG_INCLUDE_PATH
  ${ADDITIONAL_REQUIRED_VARS}
  ${VERSION_VAR}
  GLIB_VERSION)

set(GLIB_LIBRARIES ${GLIB_LIBRARY_PATH})
set(GLIB_INCLUDE_DIRS ${GLIB_INCLUDE_PATH} ${GLIBCONFIG_INCLUDE_PATH})

mark_as_advanced(
  GLIB_INCLUDE_DIRS
  GLIBCONFIG_INCLUDE_PATH
  GLIBCONFIG_INCLUDE_PATH
  GLIB_GIO_LIBRARIES
  GLIB_GIO_UNIX_LIBRARIES
  GLIB_GMODULE_LIBRARIES
  GLIB_GOBJECT_LIBRARIES
  GLIB_GTHREAD_LIBRARIES
  GLIB_LIBRARIES
  GLIB_LIBRARY_PATH
  GLIB_VERSION)
