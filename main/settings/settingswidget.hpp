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
#ifndef SETTINGSWIDGET_HPP
#define SETTINGSWIDGET_HPP

#include <QGroupBox>

namespace Ui {
class SettingsWidget;
}

class QCheckBox;

class SettingsWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

    bool isAutoRunSettingChecked() const;

signals:
    void autoRunSettingChanged(bool);

public slots:
    void setAutoRunSetting(bool);

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_HPP
