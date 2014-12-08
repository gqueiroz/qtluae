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
#
#  Description: Script for generating QtLua-Extras library.
#

include_directories(${QTLUA_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})

if(QT4_FOUND)
  set(QTLUAE_QT4_ENABLED ON)
endif()

if(Qt5_FOUND)
  set(QTLUAE_QT5_ENABLED ON)
endif()


configure_file(${QTLUAE_ABSOLUTE_ROOT_DIR}/src/QtLuaExtras/version.hpp.in
               ${CMAKE_BINARY_DIR}/qtluae_version.hpp @ONLY)

configure_file(${QTLUAE_ABSOLUTE_ROOT_DIR}/src/QtLuaExtras/config.hpp.in
               ${CMAKE_BINARY_DIR}/qtluae_config.hpp @ONLY)


file(GLOB QTLUAE_SRC_FILES ${QTLUAE_ABSOLUTE_ROOT_DIR}/src/QtLuaExtras/*.cpp)
file(GLOB QTLUAE_HDR_FILES ${QTLUAE_ABSOLUTE_ROOT_DIR}/src/QtLuaExtras/*.hpp)

set(QTLUAE_FILES ${QTLUAE_SRC_FILES} ${QTLUAE_HDR_FILES})

if(Qt5_FOUND)

  add_library(qtluae SHARED ${QTLUAE_FILES})

  target_link_libraries(qtluae ${QTLUA_LIBRARY})

  qt5_use_modules(qtluae Core Widgets)

else()

  include_directories(${CMAKE_CURRENT_BINARY_DIR})

  add_library(qtluae SHARED ${QTLUAE_FILES})

  target_link_libraries(qtluae ${QTLUA_LIBRARY}
                               ${QT_LIBRARIES})

endif()


set_target_properties(qtluae
                      PROPERTIES VERSION ${QTLUAE_VERSION_MAJOR}.${QTLUAE_VERSION_MINOR}
                                 SOVERSION ${QTLUAE_VERSION_MAJOR}.${QTLUAE_VERSION_MINOR})


if(APPLE)
  set_target_properties(qtluae PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
endif()


install(TARGETS qtluae
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${QTLUAE_HDR_FILES}
              ${CMAKE_BINARY_DIR}/qtluae_config.hpp
              ${CMAKE_BINARY_DIR}/qtluae_version.hpp
        DESTINATION include/QtLuaExtras)


