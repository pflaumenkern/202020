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
#include "settingswidgetpresenter.hpp"
#include "settings.hpp"
#include "settingswidget.hpp"

SettingsWidgetPresenter::SettingsWidgetPresenter(SettingsWidget *widget, QObject *parent)
    : QObject(parent)
    , widget(widget)
{
    if (widget) {
        widget->setAutoRunSetting(Settings::isAutoRun());
        connect(widget, &SettingsWidget::autoRunSettingChanged, this, [](bool value){
            Settings::setAutoRun(value);
        });
    }
}
