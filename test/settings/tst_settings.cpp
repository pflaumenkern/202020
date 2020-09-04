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
#include <QSettings>

#include "../../main/settings/settings.hpp"

class TestSettings : public QObject
{
    Q_OBJECT
public:
    TestSettings();
    ~TestSettings();

private slots:
    void test_isAutoRun();
    void test_setAutoRun();
};

TestSettings::TestSettings()
{

}

TestSettings::~TestSettings()
{
    Settings::setAutoRun(false);
}

void TestSettings::test_isAutoRun()
{
    bool initialAutoRunSetting = Settings::isAutoRun();

    QCOMPARE(initialAutoRunSetting, false);
}

void TestSettings::test_setAutoRun()
{
    Settings::setAutoRun(true);
    bool actualAutoRunSetting = Settings::isAutoRun();

    QCOMPARE(actualAutoRunSetting, true);
}

QTEST_APPLESS_MAIN(TestSettings)

#include "tst_settings.moc"
