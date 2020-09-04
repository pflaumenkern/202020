QT += testlib gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_settingswidgetpresenter.cpp \
    ../../main/settings/settings.cpp \
    ../../main/settings/settingswidget.cpp \
    ../../main/settings/settingswidgetpresenter.cpp

FORMS += \
    ../../main/settings/settingswidget.ui

HEADERS += \
    ../../main/settings/settings.hpp \
    ../../main/settings/settingswidget.hpp \
    ../../main/settings/settingswidgetpresenter.hpp
