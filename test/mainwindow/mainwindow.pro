QT += testlib core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += $$PWD/../../main/settings

SOURCES +=  tst_mainwindow.cpp \
    ../../main/mainwindow.cpp \
    ../../main/settings/settingswidget.cpp

HEADERS += \
    ../../main/mainwindow.hpp \
    ../../main/settings/settingswidget.hpp \
    dialogfactorystub.hpp

FORMS += \
    ../../main/mainwindow.ui \
    ../../main/settings/settingswidget.ui

RESOURCES += \
    ../../main/resources.qrc
