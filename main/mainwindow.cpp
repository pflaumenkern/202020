/**
 * Copyright (c) 2020 by it's authors.
 * Some rights reserved. See COPYING, AUTHORS.
 *
 * This file is part of 20-20-20.
 *
 * 20-20-20 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 20-20-20 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 20-20-20. If not, see <https://www.gnu.org/licenses/>.
 **/
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "mainwindowpresenter.hpp"
#include "dialogs/dialogfactory.hpp"

#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(DialogFactory *aboutFactory, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , aboutFactory(aboutFactory)
    , about(nullptr)
{
    ui->setupUi(this);
    ui->timerButton->setFocus(Qt::ActiveWindowFocusReason);

    connect(ui->timerButton, &QPushButton::clicked, this, &MainWindow::toggleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

SettingsWidget *MainWindow::settingsWidget() const
{
    return ui->settingsWidget;
}

void MainWindow::setToggleStyle(ToggleStyle style)
{
    QString icon;
    const char * text;
    if (style == RUNNING) {
        icon = ":/icons/pause.svg";
        text = "Pause";
    } else {
        icon = ":/icons/play.svg";
        text = "Start";
    }
    ui->timerButton->setIcon(QIcon(icon));
    ui->timerButton->setText(tr(text));
}

void MainWindow::setStatusMessage(const QString &message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::showAbout()
{
    if (aboutFactory) {
        if (!about) {
            about = aboutFactory->create(this);
        }
        about->open();
    } else {
        qWarning() << "No factory for about dialog provided.";
    }
}

void MainWindow::showAboutQt()
{
    QMessageBox::aboutQt(this);
}
