find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Test Sql REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.h
    ${PROJECT_SOURCE_DIR}/gemini/database/databasecore.cpp
)

add_executable (tst_databasetest tst_databasetest.cpp ${TEST_FILES})
qt5_use_modules (tst_databasetest Core Test Sql)
add_test (NAME DatabaseTest COMMAND tst_databasetest)
