find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/tools/picker.h
    ${PROJECT_SOURCE_DIR}/gemini/tools/picker.cpp
)

add_definitions (-DQUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable (quicktest_picker quicktest_picker.cpp ${TEST_FILES})
qt5_use_modules (quicktest_picker Core Quick Qml QuickTest)
add_test (NAME PickerQuickTest COMMAND quicktest_picker)
