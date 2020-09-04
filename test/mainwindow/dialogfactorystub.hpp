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
#ifndef DIALOGFACTORYSTUB_HPP
#define DIALOGFACTORYSTUB_HPP

#include <QDialog>

#include "../../main/dialogs/dialogfactory.hpp"

class DialogFactoryStub : public QDialog, public DialogFactory
{
    Q_OBJECT
public:
    DialogFactoryStub(QWidget *parent = nullptr)
        : QDialog(parent)
        , createCalled(false)
        , dialogOpened(false)
    {};

    inline QDialog *create(QWidget *parent = nullptr) override {
        Q_UNUSED(parent);

        createCalled = true;
        return this;
    }

    inline bool createHasBeenCalled() const {
        return createCalled;
    }

    inline bool openOnCreatedDialogCalled() const {
        return dialogOpened;
    }

public slots:
    void open() override {
        dialogOpened = true;
    }

private:
    bool createCalled;
    bool dialogOpened;
};

#endif // DIALOGFACTORYSTUB_HPP
