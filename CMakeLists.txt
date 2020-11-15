cmake_minimum_required(VERSION 3.16)
project(MoonCrawler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
    MoonCrawler
    main.cpp
)

# SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(MoonCrawler sfml-graphics sfml-audio)

# QT
set(Qt5_PATH  "/usr/local/opt/qt")  # TODO: windows, linux path
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(MoonCrawler Qt5::Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
