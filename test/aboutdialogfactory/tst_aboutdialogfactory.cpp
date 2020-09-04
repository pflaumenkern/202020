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
#include <QDialog>

#include "../../main/dialogs/aboutdialogfactory.hpp"

class TestAboutDialogFactory : public QObject
{
    Q_OBJECT

public:
    TestAboutDialogFactory();
    ~TestAboutDialogFactory();

private slots:
    void test_create();
    void test_create_withParent();
};

TestAboutDialogFactory::TestAboutDialogFactory()
{

}

TestAboutDialogFactory::~TestAboutDialogFactory()
{

}

void TestAboutDialogFactory::test_create()
{
    AboutDialogFactory aboutDialogFactory;

    auto dialog = aboutDialogFactory.create();

    QVERIFY(dialog != nullptr);
    QCOMPARE(dialog->parent(), nullptr);
}

void TestAboutDialogFactory::test_create_withParent()
{
    QWidget parent;
    AboutDialogFactory aboutDialogFactory;

    auto dialog = aboutDialogFactory.create(&parent);

    QVERIFY(dialog != nullptr);
    QCOMPARE(dialog->parent(), &parent);
}

QTEST_MAIN(TestAboutDialogFactory)

#include "tst_aboutdialogfactory.moc"
