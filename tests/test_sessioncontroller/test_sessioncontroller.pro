QT += testlib qml quick
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

HEADERS += \
    $${APP_PATH}/src/data/pageitem.h \
    $${APP_PATH}/src/controllers/sessioncontroller.h \
    $${APP_PATH}/src/tools/playlist.h \
    $${APP_PATH}/src/data/playlistdata.h \
    $${APP_PATH}/src/data/songdata.h \
    $${APP_PATH}/src/data/wallpaper.h

SOURCES += \
    $${APP_PATH}/src/controllers/sessioncontroller.cpp \
    $${APP_PATH}/src/tools/playlist.cpp \
    tst_sessioncontrollertest.cpp
