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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_helpWindow(NULL)
{
    m_ui->setupUi(this);
    m_ui->plainTextEdit->setReadOnly(true);

    QPalette palette = m_ui->plainTextEdit->palette();
    palette.setColor(QPalette::Base, palette.color(QPalette::Window));
    m_ui->plainTextEdit->setPalette(palette);

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
}

MainWindow::~MainWindow()
{
    if(m_helpWindow)
        delete m_helpWindow;
    delete m_ui;
}

void MainWindow::calc()
{
    if(m_ui->lineEdit->text().isEmpty())
        return;
    const double x = m_ui->lineEdit_2->text().toDouble();
    const double y = m_ui->lineEdit_3->text().toDouble();
    const double z = m_ui->lineEdit_4->text().toDouble();
    QString text = m_ui->lineEdit->text();
    m_evaluator.reset_vars();
    if(!m_ui->lineEdit_2->text().isEmpty())
        m_evaluator.set_var("x", x);
    if(!m_ui->lineEdit_3->text().isEmpty())
        m_evaluator.set_var("y", y);
    if(!m_ui->lineEdit_4->text().isEmpty())
        m_evaluator.set_var("z", z);
    bool status = m_evaluator.parse(text.toStdString());
    text += QString::fromLatin1("=");
    double result;
    if(status && m_evaluator.calculate(result))
    {
        text += QString::number(result);
        if(!m_ui->lineEdit_2->text().isEmpty())
            text += QString::fromLatin1("   [x=") + QString::number(x) + QString::fromLatin1("]");
        if(!m_ui->lineEdit_3->text().isEmpty())
            text += QString::fromLatin1("   [y=") + QString::number(y) + QString::fromLatin1("]");
        if(!m_ui->lineEdit_4->text().isEmpty())
            text += QString::fromLatin1("   [z=") + QString::number(z) + QString::fromLatin1("]");
        m_ui->lineEdit->setText(QString::number(result));
    }
    else
    {
        text += tr("ERROR: ") + QString::fromUtf8(m_evaluator.get_error().c_str());
    }
    m_ui->plainTextEdit->appendPlainText(text);
    m_ui->lineEdit->setFocus();
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
    QMessageBox msgBox(this);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setWindowTitle(tr("About"));
    msgBox.setText(tr("<b>Calculator v%1</b>").arg(QString::fromLatin1("2.0")));
    msgBox.setInformativeText(QString::fromLatin1(
                      "<a href=\"https://fami.codefreak.ru/gitlab/peter/calculator\">https://fami.codefreak.ru/gitlab/peter/calculator</a><br>"
                      "%1: <a href=\"http://www.gnu.org/copyleft/gpl.html\">GNU GPL v3</a><br><br>"
                      "Copyright &copy; 2014-2016<br>"
                      "%2 &lt;<a href=\"mailto:peter.zhigalov@gmail.com\">peter.zhigalov@gmail.com</a>&gt;"
                      ).arg(tr("License")).arg(tr("Peter Zhigalov")));
    const QList<QLabel*> labels = msgBox.findChildren<QLabel*>();
    for(QList<QLabel*>::ConstIterator it = labels.begin(); it != labels.end(); ++it)
        (*it)->setWordWrap(false);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowIcon(QIcon(":/icons/msgbox04.ico"));
    msgBox.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!m_helpWindow)
        m_helpWindow = new HelpWindow(this);
    m_helpWindow->show();
    m_helpWindow->raise();
    m_helpWindow->activateWindow();
}
