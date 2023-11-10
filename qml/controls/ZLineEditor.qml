import QtQuick 2.12
import QtQuick.Controls 2.0


Rectangle {
    width: 96
    height: 26
    color: "lightgrey"
    border.color: "grey"

    TextInput {
        anchors.fill: parent
        anchors.margins: 2
        font.pointSize: 12
        focus: true
        onAccepted: console.log("accepted")
    }
}