cmake_minimum_required (VERSION 3.12)

project (gemini VERSION 0.0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (QT_MIN_VERSION 5.14)

set (CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

option(ERASE_DATA "Erase whole saved data (It will erase on every application startup)" OFF)
option(USE_STRINGBUILDER "Use fast concatenation" OFF)

add_compile_definitions (
    ProjectName="${PROJECT_NAME}"
    ProjectVersion="${PROJECT_VERSION}"
    OrganizationName="blooser"
    OrganizationDomain="https://github.com/blooser"
)

enable_testing ()

add_subdirectory (gemini)
add_subdirectory (tests)
