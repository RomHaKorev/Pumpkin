QT += testlib
QT += quick widgets quickwidgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

#QMAKE_CXXFLAGS += --coverage -O0
#QMAKE_LFLAGS += --coverage -O0

TEMPLATE = app

HEADERS +=


SOURCES += 	main.cpp \
    tst_colorpickerrenderertest.cpp \
    tst_colorpickerutiltest.cpp \
    tst_sevensegmenttest.cpp


DISTFILES += \
    ../src/qml/qmldir


include(../Pumpkin-test-framework/pumpkin-test-framework.pri)





win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../controlers/colorpicker/release/ -lPumpkinControlers
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../controlers/colorpicker/debug/ -lPumpkinControlers
else:unix: LIBS += -L$$OUT_PWD/../controlers/colorpicker/ -lPumpkinControlers

INCLUDEPATH += $$PWD/../controlers/colorpicker
DEPENDPATH += $$PWD/../controlers/colorpicker

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../controlers/colorpicker/release/libPumpkinControlers.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../controlers/colorpicker/debug/libPumpkinControlers.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../controlers/colorpicker/release/PumpkinControlers.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../controlers/colorpicker/debug/PumpkinControlers.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../controlers/colorpicker/libPumpkinControlers.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../indicators/sevensegments/release/ -lPumpkinSevenSegments
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../indicators/sevensegments/debug/ -lPumpkinSevenSegments
else:unix: LIBS += -L$$OUT_PWD/../indicators/sevensegments/ -lPumpkinSevenSegments

INCLUDEPATH += $$PWD/../indicators/sevensegments
DEPENDPATH += $$PWD/../indicators/sevensegments

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/sevensegments/release/libPumpkinSevenSegments.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/sevensegments/debug/libPumpkinSevenSegments.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/sevensegments/release/PumpkinSevenSegments.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/sevensegments/debug/PumpkinSevenSegments.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../indicators/sevensegments/libPumpkinSevenSegments.a
