cmake_minimum_required(VERSION 3.16)
project(MoonCrawler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FILE(GLOB_RECURSE Sources src/*.cpp)
FILE(GLOB_RECURSE QtUIs ui/*.ui)
FILE(GLOB_RECURSE QtResources resources/*.qrc)
add_executable(
        MoonCrawler
        ${Sources}
        ${QtUIs}
        ${QtResources}
)
target_include_directories(MoonCrawler PRIVATE src)

# SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(MoonCrawler sfml-graphics sfml-audio)

# QT
set(Qt5_PATH  "/usr/local/opt/qt")  # TODO: windows, linux path
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(MoonCrawler Qt5::Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# JSON
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(MoonCrawler nlohmann_json::nlohmann_json)