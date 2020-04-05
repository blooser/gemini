CONFIG += warn_on qmltestcase

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

DISTFILES += \
    tst_sessioncontrollertest.qml

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
    quicktest_sessioncontroller.cpp
