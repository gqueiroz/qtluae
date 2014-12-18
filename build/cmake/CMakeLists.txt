#  Copyright (C) 2014-2014 National Institute For Space Research (INPE) - Brazil.
#
#  This file is part of the QtLua-Extras.
#
#  QtLua-Extras is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 3 as
#  published by the Free Software Foundation.
#
#  QtLua-Extras is distributed  "AS-IS" in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY OF ANY KIND; without even the implied warranty
#  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with QtLua-Extras. See COPYING. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
#
#
#  CMake scripts for QtLua-Extras
#
#  Authors: Gilberto Ribeiro de Queiroz <gribeiro@dpi.inpe.br>
#           Pedro Ribeiro <pedro@dpi.inpe.br>
#			Raian Vargas Maretto <raian@dpi.inpe.br>
#
#  Description: Main CMake script of QtLua-Extras build system.
#

cmake_minimum_required(VERSION 2.8.7)

project(qtlua_extras)


#
# main variables for the build script
#

# variables that control the system versioning
set(QTLUAE_VERSION_MAJOR 0)
set(QTLUAE_VERSION_MINOR 1)
set(QTLUAE_VERSION_PATCH 0)
set(QTLUAE_VERSION_STATUS "alpha")
set(QTLUAE_VERSION_STRING "${QTLUAE_VERSION_MAJOR}.${QTLUAE_VERSION_MINOR}.${QTLUAE_VERSION_PATCH}-${QTLUAE_VERSION_STATUS}")
set(QTLUAE_VERSION "0x000100")

# variables storing absolute paths
set(QTLUAE_ABSOLUTE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)


#
# global definitions and includes
#

include_directories(${CMAKE_BINARY_DIR})


#
# global configurations
#

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()


#
# first check of libraries
#

find_package(Qt5 5.1 QUIET COMPONENTS Core Gui Widgets)

if(Qt5_FOUND)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

else()
  find_package(Qt4 4.6.3 REQUIRED COMPONENTS QtCore QtGui)

  include(${QT_USE_FILE})

  include_directories(${QT_INCLUDE_DIR})

  add_definitions(${QT_DEFINITIONS})

endif()

if(NOT (${CMAKE_MAJOR_VERSION} LESS 3))
	find_package(Lua REQUIRED)
else(NOT (${CMAKE_MAJOR_VERSION} LESS 3))
	find_package(Lua51 REQUIRED)
endif(NOT (${CMAKE_MAJOR_VERSION} LESS 3))

find_package(QtLua REQUIRED)


#
# build modules
#
add_subdirectory(qtluae)

