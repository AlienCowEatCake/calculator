/*
   Copyright (C) 2009, 2014-2016
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
#include "ui_mainwindow.h"
#include <QPalette>
#include <QApplication>
#include <QDesktopWidget>
#include <QPoint>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);

    QPalette palette = ui->plainTextEdit->palette();
    palette.setColor(QPalette::Base, palette.color(QPalette::Window));
    ui->plainTextEdit->setPalette(palette);

    QPoint center = QApplication::desktop()->availableGeometry().center();
    QPoint corner = QApplication::desktop()->availableGeometry().topLeft();
    center.setX(center.x() - this->width() / 2);
    center.setY(center.y() - this->height() / 2);
    if(center.x() <= corner.x() || center.y() <= corner.y())
        this->move(corner);
    else
        this->move(center);

    help = NULL;
}

MainWindow::~MainWindow()
{
    if(help) delete help;
    delete ui;
}

void MainWindow::calc()
{
    if(ui->lineEdit->text() == "") return;
    double x = ui->lineEdit_2->text().toDouble();
    double y = ui->lineEdit_3->text().toDouble();
    double z = ui->lineEdit_4->text().toDouble();
    QString text = ui->lineEdit->text();
    p.reset_vars();
    if(ui->lineEdit_2->text() != "") p.set_var("x", x);
    if(ui->lineEdit_3->text() != "") p.set_var("y", y);
    if(ui->lineEdit_4->text() != "") p.set_var("z", z);
    bool status = p.parse(text.toStdString());
    text += "=";
    double result;
    if(status && p.calculate(result))
    {
        text += QString::number(result);
        if(ui->lineEdit_2->text() != "") text += "   [x=" + QString::number(x) + "]";
        if(ui->lineEdit_3->text() != "") text += "   [y=" + QString::number(y) + "]";
        if(ui->lineEdit_4->text() != "") text += "   [z=" + QString::number(z) + "]";
        ui->lineEdit->setText(QString::number(result));
    }
    else
    {
        text += "ERROR: " + QString(p.get_error().c_str());
    }
    ui->plainTextEdit->appendPlainText(text);
    ui->lineEdit->setFocus();
}

void MainWindow::on_lineEdit_returnPressed()
{
    calc();
}

void MainWindow::on_pushButton_clicked()
{
    calc();
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox msgBox;
    msgBox.setAttribute(Qt::WA_QuitOnClose);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setWindowTitle("About");
    msgBox.setText(trUtf8("<b>Calculator v2.0</b><br>"
                          "<a href=\"https://fami.codefreak.ru/gitlab/peter/calculator\">https://fami.codefreak.ru/gitlab/peter/calculator</a><br>"
                          "License: <a href=\"http://www.gnu.org/copyleft/gpl.html\">GNU GPL v3</a><br><br>"
                          "Copyright &copy; 2009, 2014-2016<br>"
                          "Zhigalov Peter &lt;<a href=\"mailto:peter.zhigalov@gmail.com\">peter.zhigalov@gmail.com</a>&gt;"));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowIcon(QIcon(":/icons/msgbox04.ico"));
    msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(help && help->isVisible())
    {
        delete help;
        help = NULL;
    }
    else if(help)
    {
        help->show();
    }
    else
    {
        help = new HelpWindow;
        help->show();
    }
}
