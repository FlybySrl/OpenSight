QT       += widgets

TARGET = modSimple
TEMPLATE = lib
CONFIG += flysight_module

FLYSIGHT_DEPEND *= core core_app

CONFIG *= WITH_OSG

include($$PWD/../../FlysightConfig.pri)

SOURCES += modSimple.cpp

HEADERS += modSimple.h
