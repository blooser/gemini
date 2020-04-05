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

add_executable (tst_sessioncontrollertest tst_sessioncontrollertest.cpp ${TEST_FILES})
qt5_use_modules (tst_sessioncontrollertest Core Quick Qml QuickTest)
add_test (NAME SessionControllerTest COMMAND tst_sessioncontrollertest)
