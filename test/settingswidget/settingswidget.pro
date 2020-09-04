QT += testlib gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_settingswidget.cpp \
    ../../main/settings/settingswidget.cpp

FORMS += \
    ../../main/settings/settingswidget.ui

HEADERS += \
    ../../main/settings/settingswidget.hpp
