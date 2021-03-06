QT += quick

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

SOURCES += \
        main.cpp \
        treeconnector.cpp \
        verticaltreelayout.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    treeconnector.h \
    verticaltreelayout.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../indicators/SevenSegments/src-sevensegments/release/ -lPumpkinSevenSegments
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../indicators/SevenSegments/src-sevensegments/debug/ -lPumpkinSevenSegments
else:unix: LIBS += -L$$OUT_PWD/../indicators/SevenSegments/src-sevensegments/ -lPumpkinSevenSegments

INCLUDEPATH += $$PWD/../indicators/SevenSegments/src-sevensegments
DEPENDPATH += $$PWD/../indicators/SevenSegments/src-sevensegments

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/SevenSegments/src-sevensegments/release/libPumpkinSevenSegments.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/SevenSegments/src-sevensegments/debug/libPumpkinSevenSegments.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/SevenSegments/src-sevensegments/release/PumpkinSevenSegments.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../indicators/SevenSegments/src-sevensegments/debug/PumpkinSevenSegments.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../indicators/SevenSegments/src-sevensegments/libPumpkinSevenSegments.a
