find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/common/enums.h
    ${PROJECT_SOURCE_DIR}/gemini/common/utility.h
    ${PROJECT_SOURCE_DIR}/gemini/common/utility.cpp
)

add_executable (tst_utilitytest tst_utilitytest.cpp ${TEST_FILES})
qt5_use_modules (tst_utilitytest Core Quick Qml QuickTest)
add_test (NAME UtilityTest COMMAND tst_utilitytest)
