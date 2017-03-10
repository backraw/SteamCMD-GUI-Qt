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

# Copy serverlist.py to build directory before building
serverlist.target = serverlist.py
serverlist.commands = cp $$PWD/serverlist.py $$OUT_PWD/serverlist.py
serverlist.depends = FORCE

PRE_TARGETDEPS += serverlist.py
QMAKE_EXTRA_TARGETS += serverlist

SOURCES += main.cpp\
        mainwindow.cpp \
    jsonparser.cpp \
    settings.cpp \
    serverlist.cpp \
    serverwindow.cpp \
    serverlist_updatethread.cpp \
    serverwindow_addlocalinstallationdialog.cpp \
    serverwindow_removeserverthread.cpp

HEADERS  += mainwindow.h \
    json.hpp \
    jsonparser.h \
    paths.h \
    servers.h \
    settings.h \
    serverlist.h \
    serverwindow.h \
    serverlist_updatethread.h \
    serverwindow_addlocalinstallationdialog.h \
    serverwindow_removeserverthread.h

FORMS    += mainwindow.ui \
    serverwindow.ui \
    serverwindow_addlocalinstallationdialog.ui
