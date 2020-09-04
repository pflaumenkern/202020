QT += testlib gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    ../../main/dialogs/aboutdialog.cpp \
    ../../main/dialogs/aboutdialogfactory.cpp \
    tst_aboutdialogfactory.cpp

HEADERS += \
    ../../main/dialogs/aboutdialog.hpp \
    ../../main/dialogs/aboutdialogfactory.hpp

FORMS += \
    ../../main/dialogs/aboutdialog.ui
