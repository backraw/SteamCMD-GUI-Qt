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
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wpedantic

# Copy serverlist.py to build directory before building
serverlist.target = scripts/serverlist.py
serverlist.commands = cp $$PWD/scripts/serverlist.py $$OUT_PWD/serverlist.py
serverlist.depends = FORCE

PRE_TARGETDEPS += scripts/serverlist.py
QMAKE_EXTRA_TARGETS += serverlist

# Find doxygen binary
DOXYGEN_BIN = $$system(which doxygen)

# Print a message if we couldn't find it
isEmpty(DOXYGEN_BIN) {
    message("Doxygen hasn't been found! Install it to generate documentation!")
}

# Add the doxygen target if we found it
!isEmpty(DOXYGEN_BIN) {
    doxygen.target = doxygen
    doxygen.commands = cd $$PWD; $$DOXYGEN_BIN Doxyfile; rm -rf $$OUT_PWD/doc; mv $$PWD/doc $$OUT_PWD/doc;

    POST_TARGETDEPS += doxygen
    QMAKE_EXTRA_TARGETS += doxygen
}

SOURCES += main.cpp\
        mainwindow.cpp \
    serverwindow.cpp \
    serverwindow_addlocalinstallationdialog.cpp  \
    json/jsonparser.cpp \
    json/settings.cpp \
    json/serverlist.cpp

HEADERS  += mainwindow.h \
    paths.h \
    servers.h \
    serverwindow.h \
    serverwindow_addlocalinstallationdialog.h \
    json/json.hpp \
    json/jsonparser.h \
    json/settings.h \
    json/serverlist.h

FORMS    += mainwindow.ui \
    serverwindow.ui \
    serverwindow_addlocalinstallationdialog.ui
