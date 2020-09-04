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
#include "settingswidget.hpp"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    connect(ui->autoRunSetting, &QCheckBox::clicked, this, &SettingsWidget::autoRunSettingChanged);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

bool SettingsWidget::isAutoRunSettingChecked() const
{
    return ui->autoRunSetting->isChecked();
}

void SettingsWidget::setAutoRunSetting(bool isChecked)
{
    ui->autoRunSetting->setChecked(isChecked);
}
