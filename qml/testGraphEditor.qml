import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QuickQanava      2.0 as Qan
import Qt.labs.settings 1.1
import "./view"
import "./container/TabView"


ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    // 定义全局对象，通过 app 来访问
    Item {
        id: app

        // 标签页逻辑控制器
        TabViewController { id: tab_ }
        property var tab: tab_ // 通过 app.tab 来访问

        // 持久化存储
        Settings { 
            id: settings
            fileName: "./.settings_ui.ini" // 配置文件名


            property alias openPageList: tab_.openPageList
            property alias showPageIndex: tab_.showPageIndex
            property alias barIsLock: tab_.barIsLock

            property bool refresh: false // 用于刷新
            function save(){ // 手动刷新
                refresh=!refresh
            }
        }
    }

    RowLayout {
        id: mainLayout
        spacing: 10
        anchors.fill: parent

        TreeView {
            id: defaultTreeView
            anchors.top: parent.top
            model: treeModel
        }

        TabView_ { 
            id: tabEditor
        }
    }

    /*
    Graph {
        width: 1180
        height: 900
        graphModel: nodesModel
    }
    */

    /*
    Qan.Navigable {
        id: graphView
        anchors.fill: parent
        navigable: true
        gridThickColor: "#c1c1c1"
    }

    Canvas {
        id: mycanvas
        //width: 100
        //height: 200
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
            ctx.fillRect(0, 0, width, height);
        }
    }
    */
}