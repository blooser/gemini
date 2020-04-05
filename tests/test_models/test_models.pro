QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

HEADERS += \
    $${APP_PATH}/src/data/playlistdata.h \
    $${APP_PATH}/src/database/databasetables.h \
    $${APP_PATH}/src/database/databasecore.h \
    $${APP_PATH}/src/models/sqltablemodel.h \
    $${APP_PATH}/src/models/songmodel.h \
    $${APP_PATH}/src/models/wallpapermodel.h \
    $${APP_PATH}/src/models/playlistmodel.h \
    $${APP_PATH}/src/models/relationmodel.h \
    $${APP_PATH}/src/models/pendingmodel.h \
    $${APP_PATH}/src/models/readmodel.h \
    $${APP_PATH}/src/models/proxy/songsinrelations.h

SOURCES += \
    $${APP_PATH}/src/database/databasecore.cpp \
    $${APP_PATH}/src/models/sqltablemodel.cpp \
    $${APP_PATH}/src/models/songmodel.cpp \
    $${APP_PATH}/src/models/wallpapermodel.cpp \
    $${APP_PATH}/src/models/playlistmodel.cpp \
    $${APP_PATH}/src/models/relationmodel.cpp \
    $${APP_PATH}/src/models/pendingmodel.cpp \
    $${APP_PATH}/src/models/readmodel.cpp \
    $${APP_PATH}/src/models/proxy/songsinrelations.cpp \
    tst_modelstest.cpp
