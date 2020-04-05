QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

HEADERS += \
    $${APP_PATH}/src/common/enums.h \
    $${APP_PATH}/src/controllers/objectcontroller.h

SOURCES += \
    $${APP_PATH}/src/controllers/objectcontroller.cpp \
    tst_objectcontrollertest.cpp
