QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinSevenSegments

HEADERS += \
    sevensegmentsml.h \
    utils/sevensegmentsutils.h \
    segment.h \
    symbol.h \
    symbolshape.h \
    utils/symbol_p.h \
    segmentshape.h \
    symboltransformation.h \
    action.h

SOURCES += \
    sevensegmentsml.cpp \
    utils/sevensegmentsutils.cpp \
    segment.cpp \
    symbol.cpp \
    symbolshape.cpp \
    utils/symbol_p.cpp \
    segmentshape.cpp \
    symboltransformation.cpp


QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_POST_LINK = rm -f "*.gcda"
