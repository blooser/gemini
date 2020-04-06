find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/paths/paths.h
    ${PROJECT_SOURCE_DIR}/gemini/paths/paths.cpp
)

add_executable (tst_pathstest tst_pathstest.cpp ${TEST_FILES})
qt5_use_modules (tst_pathstest Core Quick Qml QuickTest)
add_test (NAME PathsTest COMMAND tst_pathstest)
