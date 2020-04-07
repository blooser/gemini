find_package (Qt5 ${QT_MIN_VERSION} COMPONENTS Core Test REQUIRED)

set (TEST_FILES
    ${PROJECT_SOURCE_DIR}/gemini/vlc/vlcmedia.h
    ${PROJECT_SOURCE_DIR}/gemini/vlc/vlcmedia.cpp
    ${PROJECT_SOURCE_DIR}/gemini/vlc/vlcmeta.h
    ${PROJECT_SOURCE_DIR}/gemini/vlc/vlcmeta.cpp
    ${PROJECT_SOURCE_DIR}/gemini/paths/paths.h
    ${PROJECT_SOURCE_DIR}/gemini/paths/paths.cpp
)

include (FindLIBVLC)

add_executable(tst_vlcmediatest tst_vlcmediatest.cpp ${TEST_FILES} ${TESTING_RESOURCES})
qt5_use_modules(tst_vlcmediatest Core Test)
target_link_libraries(tst_vlcmediatest ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
add_test(NAME VlcMediaTest COMMAND tst_vlcmediatest)
