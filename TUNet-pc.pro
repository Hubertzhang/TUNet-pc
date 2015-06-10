#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T17:30:48
#
#-------------------------------------------------
QT       += webkit
QT       += webkitwidgets
QT       += core gui
QT       += qml quick
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TUNet-pc
TEMPLATE = app

SOURCES += \
    src/user.cpp \
    src/main.cpp \
    src/controller.cpp \
    src/account.cpp \
    src/network.cpp \
    src/info.cpp \
    src/connection.cpp \
    src/dataformatter.cpp \
    src/ui.cpp

HEADERS  += \
    src/user.h \
    src/controller.h \
    src/account.h \
    src/network.h \
    src/info.h \
    src/connection.h \
    src/dataformatter.h \
    src/ui.h


QT += network

RESOURCES += \
    res/resource.qrc

OTHER_FILES +=
