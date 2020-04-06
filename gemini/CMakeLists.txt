find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Gui Widgets Quick Qml Svg Sql REQUIRED)
find_package (Qt5QuickCompiler)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)

set (COMMON_FILES
    common/deleters.h
    common/enums.h
    common/utility.cpp
    common/utility.h
)

set (CONTROLLERS_FILES
    controllers/databasecontroller.cpp
    controllers/datacontroller.cpp
    controllers/filescontroller.cpp
    controllers/modelcontroller.cpp
    controllers/objectcontroller.cpp
    controllers/sessioncontroller.cpp
    controllers/databasecontroller.h
    controllers/datacontroller.h
    controllers/filescontroller.h
    controllers/modelcontroller.h
    controllers/objectcontroller.h
    controllers/sessioncontroller.h
)

set (DATA_FILES
    data/pageitem.h
    data/playlistdata.h
    data/songdata.h
)

set (DATABASE_FILES
    database/databasecore.cpp
    database/databasecore.h
    database/databasetables.h
)

set (PATHS_FILES
    paths/paths.h
    paths/paths.cpp
)

set (MODELS_FILES
    models/pendingmodel.cpp
    models/playlistmodel.cpp
    models/relationmodel.h
    models/songmodel.h
    models/sqltablemodel.h
    models/wallpapermodel.h
    models/pendingmodel.h
    models/playlistmodel.h
    models/relationmodel.cpp
    models/songmodel.cpp
    models/sqltablemodel.cpp
    models/wallpapermodel.cpp
    models/proxy/readmodel.h
    models/proxy/readmodel.cpp
    models/proxy/songsinrelations.h
    models/proxy/songsinrelations.cpp
)

set (PROCESSES_FILES
    processes/pendableprocess.cpp
    processes/pendableprocess.h
    processes/process.cpp
    processes/processexecutor.cpp
    processes/processexecutor.h
    processes/process.h
    processes/insert/pendinginsertprocess.cpp
    processes/insert/playlistinsertprocess.cpp
    processes/insert/relationinsertprocess.cpp
    processes/insert/resumeunfinishedpendingprocess.cpp
    processes/insert/songinsertprocess.cpp
    processes/insert/wallpaperinsertprocess.cpp
    processes/insert/pendinginsertprocess.h
    processes/insert/playlistinsertprocess.h
    processes/insert/relationinsertprocess.h
    processes/insert/resumeunfinishedpendingprocess.h
    processes/insert/songinsertprocess.h
    processes/insert/wallpaperinsertprocess.h
    processes/remove/pendingremoveprocess.cpp
    processes/remove/playlistremoveprocess.cpp
    processes/remove/relationremoveprocess.cpp
    processes/remove/removemissingdataprocess.cpp
    processes/remove/songremoveprocess.cpp
    processes/remove/wallpaperremoveprocess.cpp
    processes/remove/pendingremoveprocess.h
    processes/remove/playlistremoveprocess.h
    processes/remove/relationremoveprocess.h
    processes/remove/removemissingdataprocess.h
    processes/remove/songremoveprocess.h
    processes/remove/wallpaperremoveprocess.h
)

set (TOOLS_FILES
    tools/circleprogressbar.cpp
    tools/circleprogressbar.h
    tools/picker.cpp
    tools/picker.h
    tools/player.cpp
    tools/player.h
    tools/playlist.cpp
    tools/playlist.h
)

set (VLC_FILES
    vlc/vlccore.cpp
    vlc/vlccore.h
    vlc/vlcmedia.cpp
    vlc/vlcmedia.h
    vlc/vlcmeta.cpp
    vlc/vlcmeta.h
    vlc/vlcmusic.cpp
    vlc/vlcmusic.h
    vlc/vlcplayer.cpp
    vlc/vlcplayer.h
)

set (QRC_FILES
    qml/qml.qrc
    resources/resources.qrc
)

include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/database
    ${CMAKE_CURRENT_SOURCE_DIR}/paths
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/models/proxy
    ${CMAKE_CURRENT_SOURCE_DIR}/processes
    ${CMAKE_CURRENT_SOURCE_DIR}/processes/insert
    ${CMAKE_CURRENT_SOURCE_DIR}/processes/remove
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
    ${CMAKE_CURRENT_SOURCE_DIR}/vlc
)

if (ERASE_DATA)
    add_compile_definitions(ERASE_DATA)
endif()

include (FindLIBVLC)

qtquick_compiler_add_resources (RESOURCES ${QRC_FILES})
add_executable (gemini main.cpp ${COMMON_FILES} ${CONTROLLERS_FILES} ${DATA_FILES} ${DATABASE_FILES} ${PATHS_FILES} ${MODELS_FILES} ${PROCESSES_FILES} ${TOOLS_FILES} ${VLC_FILES} ${QRC_FILES})
qt5_use_modules (gemini Core Gui Widgets Quick Qml Svg Sql)

target_link_libraries(gemini ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})

install (TARGETS gemini ${INSTALL_TARGETS_DEFAULT_ARGS})
