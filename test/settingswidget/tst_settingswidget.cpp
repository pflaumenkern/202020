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
#include <QCheckBox>

#include "../../main/settings/settingswidget.hpp"

class TestSettingsWidget : public QObject
{
    Q_OBJECT
public:
    TestSettingsWidget();
    ~TestSettingsWidget();

private slots:
    void test_autoRunSettingChanged();
    void test_setAutoRunSetting_false();
    void test_setAutoRunSetting_true();
};

TestSettingsWidget::TestSettingsWidget()
{

}

TestSettingsWidget::~TestSettingsWidget()
{

}

void TestSettingsWidget::test_autoRunSettingChanged()
{
    SettingsWidget settingsWidget;
    QSignalSpy autoRunSettingSpy(&settingsWidget, &SettingsWidget::autoRunSettingChanged);

    auto checkbox = settingsWidget.findChild<QCheckBox *>("autoRunSetting");

    QTest::mouseClick(checkbox, Qt::LeftButton);

    QCOMPARE(autoRunSettingSpy.count(), 1);
}

void TestSettingsWidget::test_setAutoRunSetting_false()
{
    SettingsWidget settingsWidget;
    QSignalSpy autoRunSettingSpy(&settingsWidget, &SettingsWidget::autoRunSettingChanged);
    auto checkbox = settingsWidget.findChild<QCheckBox *>("autoRunSetting");
    checkbox->setChecked(true);

    settingsWidget.setAutoRunSetting(false);

    QCOMPARE(autoRunSettingSpy.count(), 0);
    QCOMPARE(settingsWidget.isAutoRunSettingChecked(), false);
}

void TestSettingsWidget::test_setAutoRunSetting_true()
{
    SettingsWidget settingsWidget;
    auto initialAutoRunSettingValue = settingsWidget.isAutoRunSettingChecked();
    QSignalSpy autoRunSettingSpy(&settingsWidget, &SettingsWidget::autoRunSettingChanged);

    settingsWidget.setAutoRunSetting(true);

    QCOMPARE(autoRunSettingSpy.count(), 0);
    QCOMPARE(initialAutoRunSettingValue, false);
    QCOMPARE(settingsWidget.isAutoRunSettingChecked(), true);
}

QTEST_MAIN(TestSettingsWidget)

#include "tst_settingswidget.moc"
