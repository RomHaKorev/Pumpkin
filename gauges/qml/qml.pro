QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinGauges

HEADERS += \
    ../../core/pumpkin.h \
    ../gaugeinterface.h \
    circulargaugeqml.h \
    verticalgaugeqml.h \
    ../renderers/circulargaugerenderer.h \
    ../renderers/verticalgaugerenderer.h

SOURCES += \
    circulargaugeqml.cpp \
    verticalgaugeqml.cpp
