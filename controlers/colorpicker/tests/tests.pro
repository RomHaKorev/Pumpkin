QT += testlib
QT += quick widgets quickwidgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

QMAKE_CXXFLAGS += --coverage -O0
QMAKE_LFLAGS += --coverage -O0

TEMPLATE = app

HEADERS += tst_colorpickerutiltest.h \
    tst_colorpickerrenderertest.h


SOURCES += 	main.cpp


DISTFILES += \
    ../src/qml/qmldir

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lPumpkinControlers
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lPumpkinControlers
else:unix: LIBS += -L$$OUT_PWD/../src/ -lPumpkinControlers

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libPumpkinControlers.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libPumpkinControlers.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/PumpkinControlers.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/PumpkinControlers.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/libPumpkinControlers.a
