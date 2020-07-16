QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinSevenSegments

HEADERS += \
    sevensegmentsml.h \
    utils/segmentsdrawer.h \
    utils/numbertransformation.h \
    utils/sevensegmentsutils.h \
    segment.h \
    symbol.h

SOURCES += \
    sevensegmentsml.cpp \
    utils/segmentsdrawer.cpp \
    utils/numbertransformation.cpp \
    utils/sevensegmentsutils.cpp \
    segment.cpp \
    symbol.cpp

