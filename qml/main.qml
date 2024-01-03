import QtQuick 2.12
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3
//import MyTestImportUri  1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TabView {
        id: tabView
        width: 400
        height: 400

        Repeater{
            id: tabs
            model: ListModel{
                //tabModel
                ListElement{ text: "Dog"; iconPath: "icon_tabTest.png" }
                ListElement{ text: "cat"; iconPath: "icon_tabTest.png" }
                ListElement{ text: "aa"; iconPath: "icon_tabTest.png" }
            }
            delegate: Tab {
                required property string text
                required property string iconPath
                title: text
                //icon: iconPath
            }
        }
                    
        style: TabViewStyle {
            tab: Item {
                    implicitWidth: Math.round(textitem.implicitWidth + image.width + 20)
                    implicitHeight: Math.round(textitem.implicitHeight + 10)
                    Rectangle {
                        anchors.fill: parent
                        anchors.bottomMargin: 2
                        radius: 1
                        border.width: 1
                        border.color: "#AAA"
                        color:"transparent"
                    }
                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 1
                        anchors.bottomMargin: styleData.selected ? 0 : 2
                        radius: 1
                        gradient: Gradient{
                            GradientStop{position:0; color:styleData.selected?"#EDEDED":"#E3E3E3"}
                            GradientStop{position:1; color:styleData.selected?"#DCDCDC":"#D3D3D3"}
                        }
                    }
                    Text {
                        id: textitem
                        anchors.fill: parent
                        anchors.leftMargin: 4 + image.width
                        anchors.rightMargin: 4
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: styleData.title
                        elide: Text.ElideMiddle
                    }
                    Image {
                        id: image
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.margins: 2
                        anchors.leftMargin: 4
                        fillMode: Image.PreserveAspectFit
                        source: "../res/icons/icon_tabTest.png" // control.getTab(styleData.index).icon
                    }
                }//end Item
        }//end TabViewStyle
    } //end TabView
}//end ApplicationWindow