find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest Sql REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/data/playlistdata.h
    ${PROJECT_SOURCE_DIR}/gemini/database/databasetables.h 
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/sqltablemodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/songmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/wallpapermodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/playlistmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/relationmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/pendingmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/readmodel.h
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/songsinrelations.h
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/sqltablemodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/songmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/wallpapermodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/playlistmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/relationmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/pendingmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/readmodel.cpp
    ${PROJECT_SOURCE_DIR}/gemini/models/proxy/songsinrelations.cpp 
)

add_executable (tst_modelstest tst_modelstest.cpp ${TEST_FILES})
qt5_use_modules (tst_modelstest Core Quick Qml QuickTest Sql)
add_test (NAME ModelTest COMMAND tst_modelstest)
