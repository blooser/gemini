QT += testlib sql qml quick
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

APP_PATH = $$PWD/../../gemini

INCLUDEPATH += $${APP_PATH}/src

HEADERS += \
    $${APP_PATH}/src/common/utility.h \
    $${APP_PATH}/src/data/playlistdata.h \
    $${APP_PATH}/src/database/databasecore.h \
    $${APP_PATH}/src/database/databasetables.h \
    $${APP_PATH}/src/controllers/datacontroller.h \
    $${APP_PATH}/src/controllers/modelcontroller.h \
    $${APP_PATH}/src/controllers/filescontroller.h \
    $${APP_PATH}/src/models/readmodel.h \
    $${APP_PATH}/src/models/sqltablemodel.h \
    $${APP_PATH}/src/models/pendingmodel.h \
    $${APP_PATH}/src/models/wallpapermodel.h \
    $${APP_PATH}/src/models/songmodel.h \
    $${APP_PATH}/src/models/playlistmodel.h \
    $${APP_PATH}/src/models/relationmodel.h \
    $${APP_PATH}/src/models/proxy/songsinrelations.h \
    $${APP_PATH}/src/processes/process.h \
    $${APP_PATH}/src/processes/pendableprocess.h \
    $${APP_PATH}/src/processes/processexecutor.h \
    $${APP_PATH}/src/processes/insert/pendinginsertprocess.h \
    $${APP_PATH}/src/processes/insert/playlistinsertprocess.h \
    $${APP_PATH}/src/processes/insert/relationinsertprocess.h \
    $${APP_PATH}/src/processes/insert/songinsertprocess.h \
    $${APP_PATH}/src/processes/insert/wallpaperinsertprocess.h \
    $${APP_PATH}/src/processes/insert/resumeunfinishedpendingprocess.h \
    $${APP_PATH}/src/processes/remove/pendingremoveprocess.h \
    $${APP_PATH}/src/processes/remove/playlistremoveprocess.h \
    $${APP_PATH}/src/processes/remove/relationremoveprocess.h \
    $${APP_PATH}/src/processes/remove/songremoveprocess.h \
    $${APP_PATH}/src/processes/remove/wallpaperremoveprocess.h \
    $${APP_PATH}/src/processes/remove/removemissingdataprocess.h

SOURCES += \
    $${APP_PATH}/src/common/utility.cpp \
    $${APP_PATH}/src/database/databasecore.cpp \
    $${APP_PATH}/src/controllers/datacontroller.cpp \
    $${APP_PATH}/src/controllers/modelcontroller.cpp \
    $${APP_PATH}/src/controllers/filescontroller.cpp \
    $${APP_PATH}/src/models/readmodel.cpp \
    $${APP_PATH}/src/models/sqltablemodel.cpp \
    $${APP_PATH}/src/models/pendingmodel.cpp \
    $${APP_PATH}/src/models/wallpapermodel.cpp \
    $${APP_PATH}/src/models/songmodel.cpp \
    $${APP_PATH}/src/models/playlistmodel.cpp \
    $${APP_PATH}/src/models/relationmodel.cpp \
    $${APP_PATH}/src/models/proxy/songsinrelations.cpp \
    $${APP_PATH}/src/processes/process.cpp \
    $${APP_PATH}/src/processes/pendableprocess.cpp \
    $${APP_PATH}/src/processes/processexecutor.cpp \
    $${APP_PATH}/src/processes/insert/pendinginsertprocess.cpp \
    $${APP_PATH}/src/processes/insert/playlistinsertprocess.cpp \
    $${APP_PATH}/src/processes/insert/relationinsertprocess.cpp \
    $${APP_PATH}/src/processes/insert/songinsertprocess.cpp \
    $${APP_PATH}/src/processes/insert/wallpaperinsertprocess.cpp \
    $${APP_PATH}/src/processes/insert/resumeunfinishedpendingprocess.cpp \
    $${APP_PATH}/src/processes/remove/pendingremoveprocess.cpp \
    $${APP_PATH}/src/processes/remove/playlistremoveprocess.cpp \
    $${APP_PATH}/src/processes/remove/relationremoveprocess.cpp \
    $${APP_PATH}/src/processes/remove/songremoveprocess.cpp \
    $${APP_PATH}/src/processes/remove/wallpaperremoveprocess.cpp \
    $${APP_PATH}/src/processes/remove/removemissingdataprocess.cpp \
     tst_datacontrollertest.cpp

