cmake_minimum_required(VERSION 3.14)

project(Maze LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core OpenGl)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core OpenGl)

add_executable(Maze
    main.cpp
    globject.h
    openglwindow.cpp
    openglwindow.h
    mainwindow.cpp
    mainwindow.h
    camera.h camera.cpp
    wall.h wall.cpp
    Shaders/fragment.fsh
    Shaders/vertex.vsh
)

set(RESOURCE_FILES
    Shaders/fragment.fsh
    Shaders/vertex.vsh)

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::OpenGL)

add_custom_target(copy_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Shaders
        ${PROJECT_BINARY_DIR}/Shaders
        COMMENT "Copying shaders into binary directory")

add_dependencies(Maze copy_shaders)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Resources
        ${PROJECT_BINARY_DIR}/Resources
        COMMENT "Copying resources into binary directory")

add_dependencies(Maze copy_resources)

install(TARGETS Maze
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
