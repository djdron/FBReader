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
#include <QtWidgets/QPushButton>

#include "ZLQtDialog.h"
#include "ZLQtDialogContent.h"
#include "ZLQtDialogManager.h"
#include "../util/ZLQtUtil.h"

ZLQtDialog::ZLQtDialog(const ZLResource &resource) : QDialog(qApp->activeWindow()), myButtonNumber(0) {
	setModal(true);
	setWindowTitle(::qtString(resource[ZLDialogManager::DIALOG_TITLE].value()));

	QVBoxLayout *layout = new QVBoxLayout(this);
	QWidget *widget = new QWidget(this);
	layout->addWidget(widget);
	myTab = new ZLQtDialogContent(widget, resource);

	myButtonGroup = new QWidget(this);
	layout->addWidget(myButtonGroup);
	myButtonLayout = new QGridLayout(myButtonGroup);
}

ZLQtDialog::~ZLQtDialog() {
}

void ZLQtDialog::addButton(const ZLResourceKey &key, bool accept) {
	QPushButton *button = new QPushButton(myButtonGroup);
	button->setText(ZLQtDialogManager::qtButtonText(key));
	myButtonLayout->addWidget(button, 0, myButtonNumber++);
	connect(button, SIGNAL(clicked()), this, accept ? SLOT(accept()) : SLOT(reject()));
}

bool ZLQtDialog::run() {
	((ZLQtDialogContent*)myTab)->close();
	return exec();
}
