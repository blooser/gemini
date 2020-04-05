find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest Sql REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/data/playlistdata.h 
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.h 
    ${PROJECT_SOURCE_DIR}/gemini/database/databasetables.h 
    ${PROJECT_SOURCE_DIR}/gemini/controllers/modelcontroller.h 
    ${PROJECT_SOURCE_DIR}/gemini/controllers/filescontroller.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/sqltablemodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/pendingmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/wallpapermodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/songmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/playlistmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/relationmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/readmodel.h
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/songsinrelations.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/process.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/pendableprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/pendinginsertprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/playlistinsertprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/relationinsertprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/songinsertprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/wallpaperinsertprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/resumeunfinishedpendingprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/pendingremoveprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/playlistremoveprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/relationremoveprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/songremoveprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/wallpaperremoveprocess.h 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/removemissingdataprocess.h
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/controllers/modelcontroller.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/controllers/filescontroller.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/sqltablemodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/pendingmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/wallpapermodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/songmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/playlistmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/relationmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/readmodel.cpp
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/songsinrelations.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/process.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/pendableprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/pendinginsertprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/playlistinsertprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/relationinsertprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/songinsertprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/wallpaperinsertprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/insert/resumeunfinishedpendingprocess.cpp
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/pendingremoveprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/playlistremoveprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/relationremoveprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/songremoveprocess.cpp
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/wallpaperremoveprocess.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/processes/remove/removemissingdataprocess.cpp 
)

add_executable (tst_processestest tst_processestest.cpp ${TEST_FILES})
qt5_use_modules (tst_processestest Core Quick Qml QuickTest Sql)
add_test (NAME ProcessesTest COMMAND tst_processestest)
