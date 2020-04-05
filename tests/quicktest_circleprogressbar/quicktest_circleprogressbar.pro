CONFIG += warn_on qmltestcase
CONFIG += c++17

QT += qml quick widgets

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

DISTFILES += \
    tst_circleprogressbarquicktest.qml

HEADERS += \
    $${APP_PATH}/src/tools/circleprogressbar.h

SOURCES += \
    $${APP_PATH}/src/tools/circleprogressbar.cpp \
    quicktest_circleprogressbar.cpp
