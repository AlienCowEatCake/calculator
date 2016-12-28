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

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain(QString::fromLatin1("fami.codefreak.ru"));
    a.setOrganizationName(QString::fromLatin1("FAMI Net Team"));
    a.setApplicationName(QString::fromLatin1("Calculator"));
    a.setApplicationVersion(QString::fromLatin1("2.0"));

    MainWindow w;
    w.show();

    return a.exec();
}
