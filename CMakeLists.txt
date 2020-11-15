cmake_minimum_required(VERSION 3.16)
project(MoonCrawler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(Qt5_DIR "/usr/local/Cellar/qt/5.15.1")  # TODO: windows, linux path

add_executable(
    MoonCrawler
    main.cpp
)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(MoonCrawler sfml-graphics sfml-audio)

find_package(Qt5Widgets REQUIRED)
target_link_libraries(MoonCrawler Qt5::Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
