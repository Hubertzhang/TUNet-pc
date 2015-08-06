#-------------------------------------------------
#
# Project created by QtCreator 2015-08-05T15:12:41
#
#-------------------------------------------------

QT       -= gui

TARGET = QtHpple
TEMPLATE = lib

DEFINES += QTHPPLE_LIBRARY

SOURCES += qthpple.cpp \
    qtxmlelement.cpp \
    qtxpathquery.cpp

HEADERS += qthpple.h\
        qthpple_global.h \
    qtxmlelement.h \
    qtxpathquery.h

linux:!android {
    CONFIG += link_pkgconfig
    PKGCONFIG += libxml-2.0
}

android {
    message("* Using settings for Android.")
    INCLUDEPATH += $$PWD/include/libxml2/
    LIBS += -L$$PWD/lib -lxml2
}

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

macx {
    XCODE_PATH = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk
    INCLUDEPATH += $$XCODE_PATH/usr/include/libxml2/
    DEPENDPATH  += $$XCODE_PATH/usr/lib
    LIBS += -lxml2
}
