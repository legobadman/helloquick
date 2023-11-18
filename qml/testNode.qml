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

    MouseArea {
        id: graphEditorArea
        anchors.fill: parent
        property double factor: 1.15
        // Activate multisampling for edges antialiasing
        layer.enabled: true
        layer.samples: 8

        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
        drag.threshold: 0
        onWheel: {
            var zoomFactor = wheel.angleDelta.y > 0 ? factor : 1/factor
            var scale = draggable.scale * zoomFactor
            scale = Math.min(Math.max(minZoom, scale), maxZoom)
            if(draggable.scale == scale)
                return
            var point = mapToItem(draggable, wheel.x, wheel.y)
            draggable.x += (1-zoomFactor) * point.x * draggable.scale
            draggable.y += (1-zoomFactor) * point.y * draggable.scale
            draggable.scale = scale
        }
        onPressed: {
            if (mouse.button == Qt.MiddleButton) {
                drag.target = draggable // start drag
            }
        }
        onReleased: {
            drag.target = undefined // stop drag
        }
        onClicked:{
            
        }

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
                required property var pos

                //id: ident     //warning: Unable to assign ZNode_QMLTYPE_31_QML_35 to QString
                id: qmlnode

                arg_name: name
                arg_ident: ident
                paramModel: params
                x: pos[0]
                y: pos[1]

                MouseArea {
                    id: nodeMouseArea
                    anchors.fill: parent
                    property double factor: 1.15
                    layer.enabled: true
                    layer.samples: 8
                    hoverEnabled: false
                    acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
                    drag.threshold: 0

                    onClicked: function() {
                        tempEdge.visible = true
                        tempEdge.point1x = Qt.binding(function() { return qmlnode.x })
                        tempEdge.point1y = Qt.binding(function() { return qmlnode.y })
                        tempEdge.point2x = Qt.binding(function() { return graphEditorArea.mouseX })
                        tempEdge.point2y = Qt.binding(function() { return graphEditorArea.mouseY })
                    }
                }
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
                                    outNode.width       //��outNode�Ŀ��ȷ����仯ʱ,ǿ���䴥������,����ֻ�е�outNode.x�ƶ��Ż����, ����: ��������ʱ

                                    var socketObj = outNode.getSocketObj(fromParam[1], false)
                                    var pt = outNode.mapFromItem(socketObj, 0, 0)
                                    //console.log("x=", pt2.x)
                                    return pt.x + outNode.x
                                })

                                point1y = Qt.binding(function() {
                                    var outNode = nodes.getZNode(fromParam[0])
                                    outNode.height

                                    var socketObj = outNode.getSocketObj(fromParam[1], false)
                                    var pt = outNode.mapFromItem(socketObj, 0, 0)
                                    //console.log("y=", pt.y)
                                    return pt.y + outNode.y
                                })

                                point2x = Qt.binding(function() {
                                    var inNode = nodes.getZNode(toParam[0])
                                    inNode.width

                                    var socketObj = inNode.getSocketObj(toParam[1], true)
                                    var pt = inNode.mapFromItem(socketObj, 0, 0)
                                    return inNode.x + pt.x
                                })

                                point2y = Qt.binding(function() {
                                    var inNode = nodes.getZNode(toParam[0])
                                    inNode.height

                                    var socketObj = inNode.getSocketObj(toParam[1], true)
                                    var pt = inNode.mapFromItem(socketObj, 0, 0)
                                    return inNode.y + pt.y
                                })
                            }
                        }
                    }', appWindow)
            }
        }

        Edge {
            id: tempEdge
            visible: false
            point1x: 0
            point1y: 0
            point2x: 0
            point2y: 0
            color: "red"
            thickness: 2
        }
    }

}