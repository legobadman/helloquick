cmake_minimum_required(VERSION 2.8.12)

project(helloquick LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)


find_package(Qt5 COMPONENTS Widgets Core Quick REQUIRED)

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
    znodeitem.cpp
    znodeitem.h
    zparamitem.cpp
    zparamitem.h
    qanGrid.cpp
    qanGrid.h
    qanNavigable.cpp
    qanNavigable.h
    qanNavigablePreview.cpp
    qanNavigablePreview.h
    qanLineGrid.cpp
    qanLineGrid.h

    models/GraphModel.cpp
    models/GraphModel.h
    models/ParamsModel.cpp
    models/ParamsModel.h
    models/Descriptors.cpp
    models/Descriptors.h
    models/LinkModel.cpp
    models/LinkModel.h

    #qml:
    qml/layout.qml
    qml/main_question.qml
    qml/MessageLabel.qml
    qml/rect.qml
    qml/sidepanel.qml
    qml/main.qml
    qml/ZParam.qml
    qml/ZParam2.qml
    qml/ZNode.qml
    qml/Edge.qml
    qml/NodePair.qml
    qml/testParam.qml
    qml/testGraphEditor.qml
    qml/CustomBorder.qml
    qml/StatusBtn.qml
    qml/StatusImgBtn.qml
    qml/StatusBtnGroup.qml
    qml/StatusBtnSeperator.qml
    qml/GraphEditor.qml
    qml/Graph.qml
    qml/Socket.qml
    qml/SocketName.qml
    qml/FillSpacer.qml
    qml/FixSpacer.qml
    qml/MyNode.qml
    qml/controls/ZButton.qml
    qml/controls/ZCheckBox.qml
    qml/controls/ZColorBtn.qml
    qml/controls/ZCombobox.qml
    qml/controls/ZLineEditor.qml
    qml/controls/ZPathEditor.qml
    qml/controls/ZSlider.qml
    qml/controls/ZTextEditor.qml
    qml/controls/ZVec2Editor.qml
    qml/controls/ZVec3Editor.qml
    qml/controls/ZVec4Editor.qml
    qml/controls/VecEdit.qml
    qml/image.qml
    qml/navigable.qml
    qml/grid.qml
    qml/LineGrid.qml
)

add_executable(${PROJECT_NAME} ${source} "qml.qrc" "res/icons.qrc")

set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOUIC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOMOC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY AUTORCC ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE OFF)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE .)