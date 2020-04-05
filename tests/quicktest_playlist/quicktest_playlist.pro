CONFIG += warn_on qmltestcase
QT += sql

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

DISTFILES += \
    tst_playlistquicktest.qml

HEADERS += \
    $${APP_PATH}/src/tools/playlist.h \
    $${APP_PATH}/src/data/playlistdata.h \
    $${APP_PATH}/src/data/songdata.h \
    $${APP_PATH}/src/database/databasecore.h \
    $${APP_PATH}/src/database/databasetables.h \
    $${APP_PATH}/src/models/sqltablemodel.h \
    $${APP_PATH}/src/models/playlistmodel.h \
    $${APP_PATH}/src/models/songmodel.h

SOURCES += \
    $${APP_PATH}/src/tools/playlist.cpp \
    $${APP_PATH}/src/database/databasecore.cpp \
    $${APP_PATH}/src/models/sqltablemodel.cpp \
    $${APP_PATH}/src/models/playlistmodel.cpp \
    $${APP_PATH}/src/models/songmodel.cpp \
    quicktest_playlist.cpp
