find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Quick Qml QuickTest REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/data/pageitem.h 
    ${PROJECT_SOURCE_DIR}/gemini/controllers/sessioncontroller.h 
    ${PROJECT_SOURCE_DIR}/gemini/tools/playlist.h 
    ${PROJECT_SOURCE_DIR}/gemini/data/playlistdata.h 
    ${PROJECT_SOURCE_DIR}/gemini/data/songdata.h
    ${PROJECT_SOURCE_DIR}/gemini/controllers/sessioncontroller.cpp 
    ${PROJECT_SOURCE_DIR}/gemini/tools/playlist.cpp 
)

add_definitions (-DQUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable (quicktest_sessioncontroller quicktest_sessioncontroller.cpp ${TEST_FILES})
qt5_use_modules (quicktest_sessioncontroller Core Quick Qml QuickTest)
add_test (NAME SessionControllerQuickTest COMMAND quicktest_sessioncontroller)
