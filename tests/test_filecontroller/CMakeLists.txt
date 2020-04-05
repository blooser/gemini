find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/common/enums.h
    ${PROJECT_SOURCE_DIR}/gemini/controllers/filescontroller.h
    ${PROJECT_SOURCE_DIR}/gemini/controllers/filescontroller.cpp
)

add_executable (tst_filecontrollertest tst_filecontrollertest.cpp ${TEST_FILES})
qt5_use_modules (tst_filecontrollertest Core Quick Qml QuickTest)
add_test (NAME FileControllerTest COMMAND tst_filecontrollertest)
