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
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPushButton;
class DialogFactory;
class SettingsWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(DialogFactory *aboutFactory = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

    enum ToggleStyle {
          RUNNING
        , PAUSED
    };

    SettingsWidget *settingsWidget() const;

signals:
    void toggleClicked();

public slots:
    void setToggleStyle(ToggleStyle);
    void setStatusMessage(QString const &);

private slots:
    void showAbout();
    void showAboutQt();

private:
    Ui::MainWindow *ui;
    DialogFactory * const aboutFactory;
    QDialog *about;
};

Q_DECLARE_METATYPE(MainWindow::ToggleStyle);
#endif // MAINWINDOW_HPP
