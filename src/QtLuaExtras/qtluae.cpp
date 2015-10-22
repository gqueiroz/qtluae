/*  Copyright (C) 2014-2014 National Institute For Space Research (INPE) - Brazil.

    This file is part of the QtLua-Extras.

    QtLua-Extras is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    QtLua-Extras is distributed  "AS-IS" in the hope that it will be useful,
    but WITHOUT ANY WARRANTY OF ANY KIND; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with QtLua-Extras. See COPYING. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
 */

/*!
  \file QtLuaExtras/qtluae.cpp

  \brief The core file of QtLua-Extras.

  \author Gilberto Ribeiro de Queiroz <gribeiro@dpi.inpe.br>
  \author Pedro Ribeiro <pedro@dpi.inpe.br>

  \date 2014-2014

  \copyright GNU General Public License version 3
 */

// QtLua-Extras
#include "config.hpp"

// Qt
#include <QAction>
#include <QApplication>
#include <QComboBox>
#include <QIcon>
#include <QMenu>
#include <QToolButton>
#include <QListWidget>

// QtLua
#include <QtLua/Function>
#include <QtLua/State>

QTLUA_FUNCTION(config_qslider,
               "Config a QSlider",
               "Usage: qt.config_qslider(qobject, \"item-value\", \"another-item\")\n")
{
  meta_call_check_args(args, 1, 3, QtLua::Value::TUserData, QtLua::Value::TNumber, QtLua::Value::TNumber);

  QObject* obj = get_arg_qobject<QObject>(args, 0);

  if(obj == nullptr)
    QTLUA_THROW(qt.config_qslider, "Bad object type.");

  QSlider* slider = dynamic_cast<QSlider*>(obj);

  if(slider == nullptr)
    QTLUA_THROW(qt.config_qslider, "Provided QObject is not of type QSlider.");

  int item1 = QtLua::Function::get_arg<int>(args, 1, 1);
  int item2 = QtLua::Function::get_arg<int>(args, 2, 1);

  slider->setOrientation(static_cast<Qt::Orientation>(item1));
  slider->setTickInterval(item2);
  slider->setTickPosition(QSlider::TicksBelow);

  return QtLua::Value(0);
}

QTLUA_FUNCTION(combobox_add_item,
               "Wrap QComboBox::addItem function",
               "Usage: qt.combobox.additem(qobject, \"item-value\")\n")
{
  meta_call_check_args(args, 2, 2, QtLua::Value::TUserData, QtLua::Value::TString);

  QObject* obj = get_arg_qobject<QObject>(args, 0);

  if(obj == nullptr)
    QTLUA_THROW(qt.combobox.additem, "Bad object type.");

  QComboBox* cb = dynamic_cast<QComboBox*>(obj);

  if(cb == nullptr)
    QTLUA_THROW(qt.combobox.additem, "Provided QObject is not of type QComboBox.");

  QString item = QtLua::Function::get_arg<QString>(args, 1, "");

  cb->addItem(item);

  return QtLua::Value(0);
}

QTLUA_FUNCTION(listwidget_add_item,
               "Wrap QListWidget::addItem function",
               "Usage: qt.listwidget.additem(qobject, \"item-value\")\n")
{
  meta_call_check_args(args, 2, 2, QtLua::Value::TUserData, QtLua::Value::TString);

  QObject* obj = get_arg_qobject<QObject>(args, 0);

  if(obj == nullptr)
    QTLUA_THROW(qt.lisgwidget.additem, "Bad object type.");

  QListWidget* lw = dynamic_cast<QListWidget*>(obj);

  if(lw == nullptr)
    QTLUA_THROW(qt.listwidget.additem, "Provided QObject is not of type QListWidget.");

  QString item = QtLua::Function::get_arg<QString>(args, 1, "");

  lw->addItem(item);

  return QtLua::Value(0);
}

QTLUA_FUNCTION(set_icon,
               "Wrap setIcon(QIcon::fromTheme(\"icon-name\")) for QAction, QMenu, QToolButton",
               "Usage: qt.set_icon(qobject, \"icon-name\")\n")
{
  meta_call_check_args(args, 2, 2, QtLua::Value::TUserData, QtLua::Value::TString);

  QObject* obj = get_arg_qobject<QObject>(args, 0);

  if(obj == nullptr)
    QTLUA_THROW(scidbgui.set_qicon_fromtheme, "Bad object type.");

  QString name = QtLua::Function::get_arg<QString>(args, 1, "");

  if(name.isEmpty())
  {
    QTLUA_THROW(scidbgui.set_qicon_fromtheme, "Icon name is empty.");
  }

  if(QAction* action = dynamic_cast<QAction*>(obj))
    action->setIcon(QIcon::fromTheme(name));
  else if(QMenu* menu = dynamic_cast<QMenu*>(obj))
    menu->setIcon(QIcon::fromTheme(name));
  else if(QToolButton* button = dynamic_cast<QToolButton*>(obj))
    button->setIcon(QIcon::fromTheme(name));
  else
  {
    QTLUA_THROW(scidbgui.set_qicon_fromtheme, "Could not determine QObject super class type!");
  }

  return QtLua::Value(ls);
}

void register_qtluae_functions(QtLua::State* qtlua_state)
{
  QTLUA_FUNCTION_REGISTER(qtlua_state, "qt.", combobox_add_item);
  QTLUA_FUNCTION_REGISTER(qtlua_state, "qt.", listwidget_add_item);
  QTLUA_FUNCTION_REGISTER(qtlua_state, "qt.", set_icon);
  QTLUA_FUNCTION_REGISTER(qtlua_state, "qt.", config_qslider);
}

static QtLua::State* sg_qtlua_state(nullptr);

static QApplication* sg_app(nullptr);

extern "C"
{

int luaopen_qtluae(lua_State* L)
{
  if(QApplication::instance() == nullptr)
  {
    static int argc = 1;
    static char* argv [] = {"lua" };
    sg_app = new QApplication(argc, argv);
  }

  sg_qtlua_state = new QtLua::State(L);

  sg_qtlua_state->openlib(QtLua::QtLuaLib);
  sg_qtlua_state->openlib(QtLua::QtLib);

  register_qtluae_functions(sg_qtlua_state);

  return 0;
}

} // end extern "C"

