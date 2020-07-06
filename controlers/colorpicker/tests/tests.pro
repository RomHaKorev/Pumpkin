QT += testlib
QT += quick widgets quickwidgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

QMAKE_CXXFLAGS += --coverage -O0
QMAKE_LFLAGS += --coverage -O0

TEMPLATE = app

HEADERS += \
    ../src/qml/colorpickerqml.h \
    ../src/renderers/colorpickeranimator.h \
    ../src/renderers/colorpickerbase.h \
    ../src/renderers/colorpickerrenderer.h \
    ../src/widgets/colorpicker.h \
    ../colorpickercommon.h

SOURCES += \
    ../src/qml/colorpickerqml.cpp \
    ../src/renderers/colorpickeranimator.cpp \
    ../src/renderers/colorpickerbase.cpp \
    ../src/widgets/colorpicker.cpp \
    tst_colorpickertest.cpp
