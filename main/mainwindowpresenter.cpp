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
#include "mainwindowpresenter.hpp"
#include "settings/settings.hpp"

#include <QDialog>
#include <QTime>
#include <QTimer>

#define MINUTES_20 20

MainWindowPresenter::MainWindowPresenter(MainWindow *window, QDialog *reminder, QObject *parent)
    : QObject(parent)
    , window(window)
    , reminder(reminder)
    , timer(new QTimer(this))
{
    timer->setInterval(MS_TIMER);
    timer->setSingleShot(true);

    setupConnections();
    activateTimerIfAutoRunIsActive();
}

bool MainWindowPresenter::timerIsActive() const
{
    return timer->isActive();
}

bool MainWindowPresenter::timerIsSingleShot() const
{
    return timer->isSingleShot();
}

qint32 MainWindowPresenter::timerInterval() const
{
    return timer->interval();
}

void MainWindowPresenter::toggleTimer()
{
    auto toggleStyle = MainWindow::PAUSED;
    if (timerIsActive()) {
        timer->stop();
    } else {
        activateStatusTimer();
        timer->start();
        toggleStyle = MainWindow::RUNNING;
    }
    performStatusUpdate();
    emit toggleStyleChanged(toggleStyle);
}

void MainWindowPresenter::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    performStatusUpdate();
}

void MainWindowPresenter::setupConnections()
{
    if (window) {
        connect(window, &MainWindow::toggleClicked, this, &MainWindowPresenter::toggleTimer);
        connect(this, &MainWindowPresenter::toggleStyleChanged, window, &MainWindow::setToggleStyle);
        connect(this, &MainWindowPresenter::statusChanged, window, &MainWindow::setStatusMessage);
    }

    if (reminder) {
        connect(reminder, &QDialog::finished, timer, QOverload<>::of(&QTimer::start));
        connect(timer, &QTimer::timeout, reminder, &QDialog::show);
    }
}

void MainWindowPresenter::activateTimerIfAutoRunIsActive()
{
    if (Settings::isAutoRun()) {
        toggleTimer();
    }
}

void MainWindowPresenter::activateStatusTimer()
{
    if (!statusTimer.isActive()) {
        statusTimer.start(MS_TIMER_STATUS, this);
    }
}

void MainWindowPresenter::performStatusUpdate()
{
    QString msg;
    if (timerIsActive()) {
        msg = tr("Next reminder in %n minute(s).", nullptr, remainingMinutes());
    } else {
        msg = tr("Paused.");
    }
    emit statusChanged(msg);
}

qint32 MainWindowPresenter::remainingMinutes() const
{
    auto remainingTime = timer->remainingTime();
    auto remainingMinutes = QTime::fromMSecsSinceStartOfDay(remainingTime).minute();
    return qMin(remainingMinutes + 1, MINUTES_20); // +1 to account for seconds
}
