cmake_minimum_required(VERSION 2.8.12)

project(codeeditor LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)


find_package(Qt5 COMPONENTS Widgets Core Quick REQUIRED)

set(source
    codeeditorbackend.cpp
    codeeditorbackend.h
    linenumbers.cpp
    linenumbers.h
    main.cpp

    CodeEditor.qml
    CodeEditorTabButton.qml
    CodeEditorWindow.qml
    main.qml
)

add_executable(${PROJECT_NAME} ${source} "qml.qrc")

set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOUIC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOMOC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTORCC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE OFF)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE .)