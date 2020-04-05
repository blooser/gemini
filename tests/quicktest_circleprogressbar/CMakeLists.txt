find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest Sql REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/tools/circleprogressbar.h
    ${PROJECT_SOURCE_DIR}/gemini/tools/circleprogressbar.cpp
)

add_definitions (-DQUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable (quicktest_circleprogressbar quicktest_circleprogressbar.cpp ${TEST_FILES})
qt5_use_modules (quicktest_circleprogressbar Core Quick Qml QuickTest Sql)
add_test (NAME ProgressBarQuickTest COMMAND quicktest_circleprogressbar)
