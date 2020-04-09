find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Test REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/audio/audiofile.h
    ${PROJECT_SOURCE_DIR}/gemini/audio/audiofile.cpp
)

include (FindLIBTAG)

add_executable(tst_audiofiletest tst_audiofiletest.cpp ${TEST_FILES} ${TESTING_RESOURCES})
qt5_use_modules(tst_audiofiletest Core Test)
target_link_libraries(tst_audiofiletest ${TAGLIB_LIBRARIES})
add_test(NAME VlcMediaTest COMMAND tst_audiofiletest)
