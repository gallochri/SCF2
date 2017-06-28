#-------------------------------------------------
#
# Project created by QtCreator 2017-06-12T13:22:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCF2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    wizard.cpp \
    config.cpp

HEADERS += \
        mainwindow.h \
    wizard.h \
    config.h

FORMS += \
        mainwindow.ui \
    wizard.ui

DEFINES += APP_NAME=\\\"SCF2\\\"
VERSION = 0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

DISTFILES += \
    LICENSE \
    README.md \
    .gitignore \
    doc/L001-1r16-listino-021.pdf \
    SCFqt.desktop \
    metel/ARNLSP.txt \
    metel/BTILSP.TXT \
    metel/GEWLSP021.txt \
    metel/SNR0117.txt

RESOURCES += \
    images.qrc \
    sql.qrc
