include_directories (
    ${PROJECT_SOURCE_DIR}/gemini
)

set (CMAKE_AUTOMOC ON)

# Qt Quick test 
add_subdirectory (quicktest_circleprogressbar)
add_subdirectory (quicktest_picker)
add_subdirectory (quicktest_playlist)
add_subdirectory (quicktest_sessioncontroller)

# Qt test
add_subdirectory (test_database)
add_subdirectory (test_datacontroller)
add_subdirectory (test_filecontroller)
add_subdirectory (test_models)
add_subdirectory (test_objectcontroller)
add_subdirectory (test_paths)
add_subdirectory (test_processes)
add_subdirectory (test_sessioncontroller)
add_subdirectory (test_utility)
