#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T00:45:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SteamCMD-GUI-Qt
TEMPLATE = app

# Add C++11 support
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
