#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T17:30:48
#
#-------------------------------------------------

QT       += widgets
QT       += qml

CONFIG += C++11
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtHpple/release/ -lQtHpple
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtHpple/debug/ -lQtHpple
else:unix: LIBS += -L$$OUT_PWD/../QtHpple/ -lQtHpple

INCLUDEPATH += $$PWD/../QtHpple
DEPENDPATH += $$PWD/../QtHpple

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtHpple/release/libQtHpple.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtHpple/debug/libQtHpple.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtHpple/release/QtHpple.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QtHpple/debug/QtHpple.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QtHpple/libQtHpple.a

ios {
    iphonesimulator {
        message("iphonesimulator")
        DEFINES += iphonesimulator
        XCODE_PATH = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk
    }

    iphoneos{
        message("iphoneos")
        DEFINES += iphoneos
        XCODE_PATH = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
    }

    INCLUDEPATH += $$XCODE_PATH/usr/include/libxml2/
    DEPENDPATH  += $$XCODE_PATH/usr/lib
    LIBS += -lxml2
}

