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
#include <QtTest>

#include "../../main/settings/settings.hpp"
#include "../../main/settings/settingswidget.hpp"
#include "../../main/settings/settingswidgetpresenter.hpp"

class TestSettingsWidgetPresenter : public QObject
{
    Q_OBJECT
public:
    TestSettingsWidgetPresenter();
    ~TestSettingsWidgetPresenter();

private slots:
    void test_withoutSettingsWidget();
    void test_showAutoRunSetting();
    void test_setAutoRunSetting();
};

TestSettingsWidgetPresenter::TestSettingsWidgetPresenter()
{

}

TestSettingsWidgetPresenter::~TestSettingsWidgetPresenter()
{
    Settings::setAutoRun(false);
}

void TestSettingsWidgetPresenter::test_withoutSettingsWidget()
{
    SettingsWidgetPresenter settingsWidgetPresenter(nullptr);

    QCOMPARE(settingsWidgetPresenter.settingsWidget(), nullptr);
}

void TestSettingsWidgetPresenter::test_showAutoRunSetting()
{
    Settings::setAutoRun(true);
    SettingsWidget settingsWidget;
    SettingsWidgetPresenter settingsWidgetPresenter(&settingsWidget);

    QCOMPARE(settingsWidget.isAutoRunSettingChecked(), true);
}

void TestSettingsWidgetPresenter::test_setAutoRunSetting()
{
    Settings::setAutoRun(false);
    SettingsWidget settingsWidget;
    SettingsWidgetPresenter settingsWidgetPresenter(&settingsWidget);

    settingsWidget.autoRunSettingChanged(true);

    QCOMPARE(Settings::isAutoRun(), true);
}

QTEST_MAIN(TestSettingsWidgetPresenter)

#include "tst_settingswidgetpresenter.moc"
