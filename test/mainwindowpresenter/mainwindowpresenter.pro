QT += testlib gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += qt console warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += $$PWD/../../main/settings

SOURCES +=  tst_mainwindowpresenter.cpp \
    ../../main/mainwindow.cpp \
    ../../main/mainwindowpresenter.cpp \
    ../../main/settings/settings.cpp \
    ../../main/settings/settingswidget.cpp

HEADERS += \
    ../../main/mainwindow.hpp \
    ../../main/mainwindowpresenter.hpp \
    ../../main/settings/settings.hpp \
    ../../main/settings/settingswidget.hpp

FORMS += \
    ../../main/mainwindow.ui \
    ../../main/settings/settingswidget.ui

RESOURCES += \
    ../../main/resources.qrc
