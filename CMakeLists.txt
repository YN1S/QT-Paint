cmake_minimum_required(VERSION 3.16)

project(Paint VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui REQUIRED)

add_executable(Paint
        main.cpp
        mywindow.cpp
        mywindow.h
        paint.cpp
        paint.h

        shapes/ellipse.cpp
        shapes/ellipse.h
        shapes/rectangle.cpp
        shapes/rectangle.h
        shapes/default_shape.cpp
        shapes/default_shape.h
        shapes/shapes_types.h
        shapes/shapes_types.cpp
        shapes/triangle.cpp
        shapes/triangle.h

        strategy/action_strategy.cpp
        strategy/action_strategy.h
        strategy/connection_strategy.cpp
        strategy/connection_strategy.h
        strategy/delete_strategy.cpp
        strategy/delete_strategy.h
        strategy/move_strategy.cpp
        strategy/move_strategy.h
        strategy/shapes_strategy.cpp
        strategy/shapes_strategy.h
)

target_include_directories(Paint PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(Paint PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)
