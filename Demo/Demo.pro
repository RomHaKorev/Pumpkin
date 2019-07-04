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




win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gauges/qml/release/ -lPumpkinGauges
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gauges/qml/debug/ -lPumpkinGauges
else:unix: LIBS += -L$$OUT_PWD/../gauges/qml/ -lPumpkinGauges

INCLUDEPATH += $$PWD/../gauges/qml
DEPENDPATH += $$PWD/../gauges/qml

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/qml/release/libPumpkinGauges.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/qml/debug/libPumpkinGauges.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/qml/release/PumpkinGauges.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/qml/debug/PumpkinGauges.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../gauges/qml/libPumpkinGauges.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gauges/widgets/release/ -lPumpkinWidgetsGauges
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gauges/widgets/debug/ -lPumpkinWidgetsGauges
else:unix: LIBS += -L$$OUT_PWD/../gauges/widgets/ -lPumpkinWidgetsGauges

INCLUDEPATH += $$PWD/../gauges/widgets
DEPENDPATH += $$PWD/../gauges/widgets

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/widgets/release/libPumpkinWidgetsGauges.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/widgets/debug/libPumpkinWidgetsGauges.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/widgets/release/PumpkinWidgetsGauges.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gauges/widgets/debug/PumpkinWidgetsGauges.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../gauges/widgets/libPumpkinWidgetsGauges.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../spinners/release/ -lPumpkinSPinners
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../spinners/debug/ -lPumpkinSPinners
else:unix: LIBS += -L$$OUT_PWD/../spinners/ -lPumpkinSPinners

INCLUDEPATH += $$PWD/../spinners
DEPENDPATH += $$PWD/../spinners

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spinners/release/libPumpkinSPinners.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spinners/debug/libPumpkinSPinners.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spinners/release/PumpkinSPinners.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../spinners/debug/PumpkinSPinners.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../spinners/libPumpkinSPinners.a