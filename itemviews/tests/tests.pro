QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_treeview.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../treeview/ -ltreeview
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../treeview/ -ltreeviewd
else:unix: LIBS += -L$$OUT_PWD/../treeview/ -ltreeview

INCLUDEPATH += $$PWD/../treeview
DEPENDPATH += $$PWD/../treeview
