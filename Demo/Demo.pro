QT += quick widgets quickwidgets core gui
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    main.cpp


debug:QMAKE_CXXFLAGS += --coverage    # -fprofile-arcs -ftest-coverage
debug:QMAKE_LFLAGS   += --coverage    # -lgcov

INCLUDEPATH += $$PWD/../itemviews/treeview
DEPENDPATH += $$PWD/../itemviews/treeview


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../controlers/colorpicker/src/release/ -lPumpkinControlers
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../controlers/colorpicker/src/debug/ -lPumpkinControlers
else:unix: LIBS += -L$$OUT_PWD/../controlers/colorpicker/src/ -lPumpkinControlers

INCLUDEPATH += $$PWD/../controlers/colorpicker/src
DEPENDPATH += $$PWD/../controlers/colorpicker/src


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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../indicators/gauges/release/ -lPumpkinGauges
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../indicators/gauges/debug/ -lPumpkinGauges
else:unix: LIBS += -L$$OUT_PWD/../indicators/gauges/ -lPumpkinGauges

INCLUDEPATH += $$PWD/../indicators/gauges
DEPENDPATH += $$PWD/../indicators/gauges

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/gauges/release/libPumpkinGauges.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/gauges/debug/libPumpkinGauges.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/gauges/release/PumpkinGauges.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/gauges/debug/PumpkinGauges.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../indicators/gauges/libPumpkinGauges.a


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
