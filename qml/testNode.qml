import QtQuick 2.12
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Repeater{
        id: nodes
        model: nodesModel

        function idxFromId(ident) {
            var idx = nodesModel.indexFromId(ident)
            //console.log(idx)
        }

        function getZNode(ident) {
            var idx = nodesModel.indexFromId(ident)
            if (idx == -1) {
                return null
            } else {
                return nodes.itemAt(idx)
            }
        }

        delegate: ZNode {
            required property string name
            required property string ident
            required property variant params

            //id: ident     //warning: Unable to assign ZNode_QMLTYPE_31_QML_35 to QString
            arg_name: name
            arg_ident: ident
            paramModel: params
            x: 200
            y: 150
        }

        Component.onCompleted: {
            var edgesContainer = Qt.createQmlObject('
                import QtQuick 2.12
                import QtQuick.Controls 1.2
                import QtQuick.Layouts 1.3
                import QtQuick.Controls 1.4
                import QtQuick.Controls.Styles 1.4

                Repeater {
                    model: nodesModel.getLinkModel()

                    delegate: Edge {

                        required property var fromParam
                        required property var toParam

                        id: edge233
                        visible: true
                        point1x: 0
                        point1y: 0
                        point2x: 0
                        point2y: 0
                        color: "blue"

                        Component.onCompleted: {
                            point1x = Qt.binding(function() {
                                var outNode = nodes.getZNode(fromParam[0])
                                var socketObj = outNode.getSocketObj(fromParam[1], false)
                                var pt = outNode.mapFromItem(socketObj, 0, 0)
                                //console.log("x=", pt.x)
                                return pt.x + outNode.x
                            })

                            point1y = Qt.binding(function() {
                                var outNode = nodes.getZNode(fromParam[0])
                                var socketObj = outNode.getSocketObj(fromParam[1], false)
                                var pt = outNode.mapFromItem(socketObj, 0, 0)
                                //console.log("y=", pt.y)
                                return pt.y + outNode.y
                            })

                            point2x = Qt.binding(function() {
                                var inNode = nodes.getZNode(toParam[0])
                                var socketObj = inNode.getSocketObj(toParam[1], true)
                                var pt = inNode.mapFromItem(socketObj, 0, 0)
                                return inNode.x + pt.x
                            })

                            point2y = Qt.binding(function() {
                                var inNode = nodes.getZNode(toParam[0])
                                var socketObj = inNode.getSocketObj(toParam[1], true)
                                var pt = inNode.mapFromItem(socketObj, 0, 0)
                                return inNode.y + pt.y
                            })
                        }
                    }
                }', appWindow)
        }
    }


    Component.onCompleted: {
        
    }

    /*
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton

        onClicked: mouseArea.forceActiveFocus()  //make all textInput focus out: https://stackoverflow.com/questions/55101332/how-to-achieve-click-an-area-outside-the-textfield-to-make-the-textfield-lose-fo

        ZNode {
            id: yyy_CreateCube
            name: "CreateCube"
        }

        ZNode {
            id: xxx_CreateSphere
            name: "CreateSphereCreateSphereCreateSphere"
            x: 200
            y: 150
        }

        Edge {
            id: edgetest
            visible: true
            point1x: yyy_CreateCube.x
            point1y: yyy_CreateCube.y
            point2x: xxx_CreateSphere.x
            point2y: xxx_CreateSphere.y
            color: "blue"
            thickness: 2
        }
    }
    */
}