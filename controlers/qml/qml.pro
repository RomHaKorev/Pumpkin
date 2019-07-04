QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinControlers

HEADERS += \
    colorpickerqml.h \
    ../renderers/colorpickerrenderer.h

SOURCES += \
    colorpickerqml.cpp

