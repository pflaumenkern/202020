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
#ifndef MAINWINDOWPRESENTER_HPP
#define MAINWINDOWPRESENTER_HPP

#include <QObject>
#include <QBasicTimer>

#include "mainwindow.hpp"

class QDialog;
class QTimer;

class MainWindowPresenter : public QObject
{
    Q_OBJECT

public:
    explicit MainWindowPresenter(MainWindow *window, QDialog *reminder, QObject *parent = nullptr);

    bool timerIsActive() const;
    bool timerIsSingleShot() const;
    qint32 timerInterval() const;

    inline bool statusTimerIsActive() const {
        return statusTimer.isActive();
    }

    inline QTimer const *reminderTimer() const {
        return timer;
    }

signals:
    void toggleStyleChanged(MainWindow::ToggleStyle);
    void statusChanged(QString const &);

public slots:
    void toggleTimer();

protected:
    void timerEvent(QTimerEvent *) override;

private:
    MainWindow * const window;
    QDialog * const reminder;
    QTimer * const timer;
    QBasicTimer statusTimer;

    void setupConnections();
    void activateTimerIfAutoRunIsActive();
    void activateStatusTimer();
    void performStatusUpdate();

    qint32 remainingMinutes() const;

    static const qint32 MS_TIMER = 1200000; // 20 minutes
    static const qint32 MS_TIMER_STATUS = 5000;
};

#endif // MAINWINDOWPRESENTER_HPP
