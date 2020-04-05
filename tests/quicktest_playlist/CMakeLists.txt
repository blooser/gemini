find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest Sql REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/tools/playlist.h
    ${PROJECT_SOURCE_DIR}/gemini/data/playlistdata.h 
    ${PROJECT_SOURCE_DIR}/gemini/data/songdata.h 
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.h 
    ${PROJECT_SOURCE_DIR}/gemini/database/databasetables.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/sqltablemodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/playlistmodel.h 
    ${PROJECT_SOURCE_DIR}/gemini/models/songmodel.h
    ${PROJECT_SOURCE_DIR}/gemini/tools/playlist.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/sqltablemodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/playlistmodel.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/models/songmodel.cpp 
)

add_definitions (-DQUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable (quicktest_playlist quicktest_playlist.cpp ${TEST_FILES})
qt5_use_modules (quicktest_playlist Core Quick Qml QuickTest Sql)
add_test (NAME PlaylistQuickTest COMMAND quicktest_playlist)

