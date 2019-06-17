QT += widgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinWidgetsGauges


HEADERS += \
    circulargauge.h \
    verticalgauge.h

SOURCES += \
    circulargauge.cpp \
    verticalgauge.cpp
