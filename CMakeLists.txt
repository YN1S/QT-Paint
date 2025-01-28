cmake_minimum_required(VERSION 3.16)

project(Paint VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

add_executable(Paint
        main.cpp
        drawingwidget.cpp
        drawingwidget.h
        mainwindow.cpp
        mainwindow.h
)

target_include_directories(Paint PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(Paint PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
