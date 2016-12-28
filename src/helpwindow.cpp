/*
   Copyright (C) 2014, 2016
        Peter Zhigalov <peter.zhigalov@gmail.com>

   This file is part of the `calculator' program.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "helpwindow.h"
#include "ui_helpwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPoint>

HelpWindow::HelpWindow(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::HelpWindow)
{
    m_ui->setupUi(this);

    QPoint center;
    if(parent)
        center = parent->geometry().center();
    else
        center = QApplication::desktop()->availableGeometry().center();
    QPoint corner = QApplication::desktop()->availableGeometry().topLeft();
    center.setX(center.x() - width() / 2);
    center.setY(center.y() - height() / 2);
    if(center.x() <= corner.x() || center.y() <= corner.y())
        move(corner);
    else
        move(center);

    setWindowFlags(Qt::Dialog
                 | Qt::MSWindowsFixedSizeDialogHint
                 | Qt::CustomizeWindowHint
                 | Qt::WindowTitleHint
                 | Qt::WindowCloseButtonHint
                  );
}

HelpWindow::~HelpWindow()
{
    delete m_ui;
}
