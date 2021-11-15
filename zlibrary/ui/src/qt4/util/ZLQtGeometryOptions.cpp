/*
 * Copyright (C) 2004-2013 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#include "ZLQtGeometryOptions.h"

static const std::string OPTIONS = "Options";

ZLQtGeometryOptions::ZLQtGeometryOptions(const std::string &prefix) :
	myX(ZLCategoryKey::LOOK_AND_FEEL, OPTIONS, prefix + "XPosition", 0, QApplication::desktop()->width()*0.9f, QApplication::desktop()->width()*(prefix.empty() ? 0.1f : 0.25f)),
	myY(ZLCategoryKey::LOOK_AND_FEEL, OPTIONS, prefix + "YPosition", 0, QApplication::desktop()->height()*0.9f, QApplication::desktop()->height()*(prefix.empty() ? 0.1f : 0.25f)),
	myWidth(ZLCategoryKey::LOOK_AND_FEEL, OPTIONS, prefix + "Width", 10, QApplication::desktop()->width(), QApplication::desktop()->width()*(prefix.empty() ? 0.8f : 0.5f)),
	myHeight(ZLCategoryKey::LOOK_AND_FEEL, OPTIONS, prefix + "Height", 10, QApplication::desktop()->height(), QApplication::desktop()->height()*(prefix.empty() ? 0.8f : 0.5f))
  {
}

void ZLQtGeometryOptions::getFromWidget(const QWidget &widget) {
	QRect r = widget.geometry();
	if (r.left() != -1) {
		myX.setValue(r.left());
	}
	if (r.top() != -1) {
		myY.setValue(r.top());
	}
	myWidth.setValue(r.width());
	myHeight.setValue(r.height());
}

void ZLQtGeometryOptions::setToWidget(QWidget &widget) const {
	widget.setGeometry(myX.value(), myY.value(), myWidth.value(), myHeight.value());
}
