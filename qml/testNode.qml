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

    //Graph {
    //    anchors.fill: parent
    //}

    //ZNode {
    //    id: yyy_CreateCube
    //    name: "CreateCube"
    //}

    Repeater{
        model: nodesModel

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
    }
    Repeater {
        model: nodesModel.getLinkModel()
        delegate: Text {
            required property var fromParam
            required property var toParam

            text: fromParam[0] + ":" + fromParam[1] + "->" + toParam[0] + ":" + toParam[1]
        }
    }

    /*
    Repeater {
        model: linksModel

        delegate: Edge {
            required property string fromSock
            required property string toSock

            id: wtf
            visible: true
            point1x: 0
            point1y: 0
            point2x: 0
            point2y: 0
            color: "blue"
        }
    }
    */


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