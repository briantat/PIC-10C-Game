#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T00:23:32
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp \
    quitwidget.cpp \
    instwidget.cpp \
    endgame.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    quitwidget.h \
    instwidget.h \
    endgame.h

FORMS    += mainwindow.ui \
    quitwidget.ui \
    gameboard.ui

CONFIG += c++11

RESOURCES += \
    Images.qrc \
    sounds.qrc

DISTFILES +=
