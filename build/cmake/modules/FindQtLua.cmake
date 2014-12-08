#
# Find QtLua
#
# Find QtLua include directory and libraries.
#
# QTLUA_INCLUDE_DIR    - where to find QtLua header files.
# QTLUA_LIBRARY        - where to find QtLua library for C++.
# QTLUA_FOUND          - True if QtLua found.
#
# Author: Gilberto Ribeiro de Queiroz <gribeiro@dpi.inpe.br>
#

find_path(QTLUA_INCLUDE_DIR QtLua/qtluavalue.hh
          PATHS /usr
                /usr/local
          PATH_SUFFIXES include
                        include/qt4)

find_library(QTLUA_LIBRARY
             NAMES qtlua
             PATHS /usr
                   /usr/local
             PATH_SUFFIXES lib)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(QtLua DEFAULT_MSG QTLUA_INCLUDE_DIR QTLUA_LIBRARY)

mark_as_advanced(QTLUA_INCLUDE_DIR QTLUA_LIBRARY)


