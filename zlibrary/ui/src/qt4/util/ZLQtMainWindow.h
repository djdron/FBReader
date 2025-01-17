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

#ifndef __ZLQTMAINWINDOW_H__
#define __ZLQTMAINWINDOW_H__

#include <string>

#include <QtWidgets/QMainWindow>

#include <ZLOptions.h>

#include "ZLQtGeometryOptions.h"

class QWidget;
class QToolBar;

class ZLQtMainWindow : public QMainWindow {
	Q_OBJECT

protected:
	ZLQtMainWindow(QWidget *parent, const std::string &windowName);

	void moveEvent(QMoveEvent* event);
	void resizeEvent(QResizeEvent* event);
	void closeEvent(QCloseEvent* event);

public:
	void showWithGeometry();

private:
	void saveWindowGeometry();

	enum WindowSizeState {
		NORMAL,
		MAXIMIZED,
		FULLSCREEN
	};

protected:
	QToolBar *myToolbar;
	QTimer* timer;

private:
	const std::string myOptionPrefix;

	ZLIntegerOption myWindowStateOption;
	ZLQtGeometryOptions myGeometryOptions;
};

#endif /* __ZLQTMAINWINDOW_H__ */
