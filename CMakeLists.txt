cmake_minimum_required(VERSION 2.8.12)

project(helloquick LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)


find_package(Qt5 COMPONENTS Core Quick REQUIRED)

#file(GLOB_RECURSE source CONFIGURE_DEPENDS *.h *.cpp *.ui *.qml)

set(source
    main.cpp
    common.h
    selfdefinedqmltype.cpp
    selfdefinedqmltype.h
    mytest.h
    mytest.cpp
    quick_edge.cpp
    quick_edge.h
    quick_node.cpp
    quick_node.h
    quick_parameter.cpp
    quick_parameter.h
    quick_graph.cpp
    quick_graph.h
    #qml:
    qml/layout.qml
    qml/main_question.qml
    qml/MessageLabel.qml
    qml/rect.qml
    qml/sidepanel.qml
    qml/main.qml
    qml/ZParam.qml
    qml/ZNode.qml
    qml/testParam.qml
    qml/testNode.qml
    qml/CustomBorder.qml
    qml/StatusBtn.qml
    qml/StatusBtnGroup.qml
    qml/StatusBtnSeperator.qml
    qml/Socket.qml
)

add_executable(${PROJECT_NAME} ${source} "qml.qrc")

set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOUIC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOMOC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTORCC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE OFF)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)