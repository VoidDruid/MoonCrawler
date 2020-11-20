cmake_minimum_required(VERSION 3.16)
project(MoonCrawler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

FILE(GLOB_RECURSE Sources src/*.cpp)
FILE(GLOB_RECURSE QtResources resources/*.qrc)
add_executable(
        MoonCrawler
        ${Sources}
        ${QtResources}
)
target_include_directories(MoonCrawler PRIVATE src)
target_include_directories(MoonCrawler PRIVATE include/ui)  # for moc

# SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(MoonCrawler sfml-graphics sfml-audio)

# QT
set(Qt5_DIR  "/usr/local/opt/qt/lib/cmake/qt5")  # TODO: windows, linux path
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(MoonCrawler Qt5::Widgets)

# JSON
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(MoonCrawler nlohmann_json::nlohmann_json)