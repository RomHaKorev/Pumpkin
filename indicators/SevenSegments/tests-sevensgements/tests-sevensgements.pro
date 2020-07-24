QT += testlib
QT += quick widgets quickwidgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

#QMAKE_CXXFLAGS += --coverage -O0
#QMAKE_LFLAGS += --coverage -O0

include(../../../Pumpkin-test-framework/pumpkin-test-framework.pri)

TEMPLATE = app

HEADERS +=


SOURCES += 	main.cpp \
    tst_sevensegmenttest.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src-sevensegments/release/ -lPumpkinSevenSegments
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src-sevensegments/debug/ -lPumpkinSevenSegments
else:unix: LIBS += -L$$OUT_PWD/../src-sevensegments/ -lPumpkinSevenSegments

INCLUDEPATH += $$PWD/../src-sevensegments
DEPENDPATH += $$PWD/../src-sevensegments

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src-sevensegments/release/libPumpkinSevenSegments.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src-sevensegments/debug/libPumpkinSevenSegments.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src-sevensegments/release/PumpkinSevenSegments.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src-sevensegments/debug/PumpkinSevenSegments.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src-sevensegments/libPumpkinSevenSegments.a
