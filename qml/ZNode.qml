import QtQuick 2.12
import QtQuick.Layouts 1.3
import ZQuickNode 1.0
import ZQuickParam 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4



Rectangle {
    id: qmlnode
    property string ident
    property string name
    //property list<ZParam> params

    color: "black"

    CustomBorder
    {
        commonBorderWidth: 2
        borderColor: "black"
    }

    implicitWidth:  mainLayout.implicitWidth
    implicitHeight: mainLayout.implicitHeight

    ZQuickNode {
        id: thisnode
        name: parent.name
    }

    ColumnLayout  {
        id: mainLayout
        spacing: 1
        anchors.fill: parent

        Rectangle {
            id: node_header
            color: "#246283"
            //color: "transparent"
            implicitWidth: header_layout.implicitWidth + header_layout.anchors.margins * 2
            implicitHeight: header_layout.implicitHeight + header_layout.anchors.margins * 2
            Layout.fillWidth: true

            RowLayout {
                id: header_layout
                anchors.fill: parent
                anchors.margins: 8

                Text {
                   id: btnshowparams
                   text: thisnode.name
                   font.family: "Consolas"
                   font.pixelSize: 20;
                   font.bold: true;
                   color: "white"
                }
            }
        }

        Rectangle {
            id: node_body
            color: "#303030"

            implicitWidth:  bodyLayout.implicitWidth
            implicitHeight: bodyLayout.implicitHeight

            ColumnLayout {
                id: bodyLayout

                ZParam {
                    id: param1
                    name: "position"
                }

                ZParam {
                    id: param2
                    name: "Noise Element Size"
                }
            }
        }
    }

    MouseArea {
        id: mouseArea1
        anchors.fill: parent
        drag.target: parent
        /*
        onPressed: {
            //qmlnode.beginDrag = Qt.point(qmlnode.x, qmlnode.y);
        }
        onReleased: {
            
        }
        */
    }

    Connections {
        target: thisnode
        function onNewparamCommand()
        {
            //params.add(new ZParam {name:"param3"})
            console.log("onNewparamCommand")
        }
    }
}
