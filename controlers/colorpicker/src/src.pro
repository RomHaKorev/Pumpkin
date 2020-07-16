QT += quick widgets quickwidgets
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 staticlib
TARGET = PumpkinControlers

HEADERS += \
    common/util/colortoangleconverter.h \
    common/util/cursorcolorizer.h \
    qml/colorpickerqml.h \
	common/colorpickerrenderer.h \
	common/colorpickerrendererbase.h \
	widgets/colorpicker.h \
	common/colorpickeranimator.h \
	common/colorpickerbase.h

SOURCES += \
    common/colorpickerrenderer.cpp \
	common/colorpickeranimator.cpp \
	common/colorpickerbase.cpp \
    common/util/colortoangleconverter.cpp \
    common/util/cursorcolorizer.cpp \
	qml/colorpickerqml.cpp \
	widgets/colorpicker.cpp


