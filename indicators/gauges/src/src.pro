QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinGauges

HEADERS += \
    common/circulargaugerenderer.h \
    common/verticalgaugerenderer.h \
    qml/circulargaugeqml.h \
    qml/pumpkin_gauges_plugin.h \
    qml/verticalgaugeqml.h \
    widgets/circulargauge.h \
    widgets/verticalgauge.h \
    pumpkin_gauges.h \
    common/gaugeinterface.h

SOURCES += \
    qml/circulargaugeqml.cpp \
    qml/pumpkin_gauges_plugin.cpp \
    qml/verticalgaugeqml.cpp \
    widgets/circulargauge.cpp \
    widgets/verticalgauge.cpp
