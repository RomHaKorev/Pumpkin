QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinControlers

HEADERS += \
    qml/colorpickerqml.h \
    renderers/colorpickerrenderer.h \
    renderers/colorpickerrendererbase.h \
    widgets/colorpicker.h \
    renderers/colorpickeranimator.h \
    renderers/colorpickerbase.h

SOURCES += \
    qml/colorpickerqml.cpp \
    widgets/colorpicker.cpp \
    renderers/colorpickeranimator.cpp \
    renderers/colorpickerbase.cpp


