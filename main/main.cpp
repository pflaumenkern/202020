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
#include "mainwindowpresenter.hpp"
#include "dialogs/aboutdialogfactory.hpp"
#include "dialogs/reminderdialog.hpp"
#include "settings/settingswidgetpresenter.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationDomain("pflaumenkern.dev");
    QApplication::setOrganizationName("Matthias Reißer");
    QApplication::setApplicationName("20-20-20");
    QApplication::setApplicationVersion("1.0.1");

    AboutDialogFactory aboutDialogFactory;
    ReminderDialog reminderDialog;
    MainWindow window(&aboutDialogFactory);
    MainWindowPresenter presenter(&window, &reminderDialog);
    SettingsWidgetPresenter settingsWidgetPresenter(window.settingsWidget());

    window.show();
    return a.exec();
}
