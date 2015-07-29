QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demoOpenSight
TEMPLATE = app

CONFIG *= demo

FLYSIGHT_DEPEND *= core core_app

include($$PWD/../../FlysightConfig.pri)

SOURCES += main.cpp\
        demoOpenSight.cpp

HEADERS  += demoOpenSight.h

FORMS    +=
