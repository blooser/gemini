CONFIG += warn_on qmltestcase
CONFIG += c++17

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

DISTFILES += \
    tst_pickertest.qml

HEADERS += \
    $${APP_PATH}/src/tools/picker.h

SOURCES += \
    $${APP_PATH}/src/tools/picker.cpp \
    quicktest_picker.cpp
