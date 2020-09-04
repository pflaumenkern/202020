QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/settings

SOURCES += \
    dialogs/aboutdialog.cpp \
    dialogs/aboutdialogfactory.cpp \
    dialogs/reminderdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowpresenter.cpp \
    settings/settings.cpp \
    settings/settingswidget.cpp \
    settings/settingswidgetpresenter.cpp

HEADERS += \
    dialogs/aboutdialog.hpp \
    dialogs/aboutdialogfactory.hpp \
    dialogs/dialogfactory.hpp \
    dialogs/reminderdialog.hpp \
    mainwindow.hpp \
    mainwindowpresenter.hpp \
    settings/settings.hpp \
    settings/settingswidget.hpp \
    settings/settingswidgetpresenter.hpp

FORMS += \
    dialogs/aboutdialog.ui \
    dialogs/reminderdialog.ui \
    mainwindow.ui \
    settings/settingswidget.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    translations/main_de_DE.ts
