find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/helpers/pathhelper.h
)

add_executable (tst_pathhelpertest tst_pathhelpertest.cpp ${TEST_FILES})
qt5_use_modules (tst_pathhelpertest Core Quick Qml QuickTest)
add_test (NAME PathHelperTest COMMAND tst_pathhelpertest)
