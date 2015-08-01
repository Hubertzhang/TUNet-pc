#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T17:30:48
#
#-------------------------------------------------
QT       += webkit
QT       += webkitwidgets
QT       += widgets
QT       += qml

TARGET = TUNet-pc
TEMPLATE = app

SOURCES += \
    src/backend/BasicNetworkService.cpp \
    src/backend/UseregPageService.cpp \
    src/backend/NetPageService.cpp \
    src/ui/InterfaceEngine.cpp \
    src/ui/AccountInfoInterface.cpp \
    src/ui/OnlineStateInterface.cpp \
    src/NetworkAssistant.cpp \
    src/Main.cpp \
    src/DataFormatter.cpp \

HEADERS  += \
    src/backend/NetworkInfoType.h \
    src/backend/BasicNetworkService.h \
    src/backend/UseregPageService.h \
    src/backend/NetPageService.h \
    src/ui/InterfaceEngine.h \
    src/ui/AccountInfoInterface.h \
    src/ui/OnlineStateInterface.h \
    src/NetworkAssistant.h \
    src/DataFormatter.h \

QT += network

RESOURCES += \
    res/resource.qrc

OTHER_FILES +=
