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

#ifndef __ZLQTOPTIONSDIALOG_H__
#define __ZLQTOPTIONSDIALOG_H__

#include <QtWidgets/QDialog>

#include <ZLOptionsDialog.h>

#include "../util/ZLQtGeometryOptions.h"

class QListWidget;
class QStackedLayout;

class ZLQtOptionsDialog : public QDialog, public ZLOptionsDialog {
	Q_OBJECT

public:
	ZLQtOptionsDialog(const ZLResource &resource, shared_ptr<ZLRunnable> applyAction);
	ZLDialogContent &createTab(const ZLResourceKey &pageKey, const ZLResourceKey &tabKey);

protected:
	bool run();

private Q_SLOTS:
	void apply();
	void selectPage(int index);
	void selectTab(int index);
	void storeGeometry();

private:
	QListWidget *myCategoryList;
	QStackedLayout *myStack;
	ZLQtGeometryOptions myGeometryOptions;
	ZLStringOption mySelectedTabOption;
};

#endif /* __ZLQTOPTIONSDIALOG_H__ */
