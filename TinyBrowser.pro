#-------------------------------------------------
#
# Project created by QtCreator 2012-07-05T17:41:50
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = TinyBrowser
TEMPLATE = app

CONFIG (debug, debug|release) {
    DESTDIR = debug/
    OBJECTS_DIR = debug/gen
    MOC_DIR = debug/gen
    RCC_DIR = debug/gen
} else {
    DESTDIR = release/
    OBJECTS_DIR = release/gen
    MOC_DIR = release/gen
    RCC_DIR = release/gen
}

SOURCES +=  src/main.cpp \
            src/main/mainwindow.cpp \
            src/widgets/tabframe.cpp \
            src/widgets/urllineedit.cpp \
            src/widgets/webviewfortabs.cpp \
            src/widgets/browsertabwidget.cpp \
            src/widgets/browsertabbar.cpp \
            src/other/global.cpp \
            src/widgets/webpagefortab.cpp

HEADERS  += src/main/mainwindow.h \
            src/widgets/tabframe.h \
            src/widgets/urllineedit.h \
            src/widgets/webviewfortabs.h \
            src/widgets/browsertabwidget.h \
            src/widgets/browsertabbar.h \
            src/other/global.h \
            src/widgets/webpagefortab.h

FORMS    += src/main/mainwindow.ui \
            src/widgets/tabframe.ui
