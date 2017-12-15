import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    property alias title: lblText.text
    property alias textColor: lblText.color
    property alias lineColor: line.color
    property alias lineVisible: line.visible

    anchors.left: parent.left
    anchors.right: parent.right
    height: lblText.height+2

    Text {
        id: lblText
        anchors.top: parent.top
        text: ""
        wrapMode: Text.WordWrap
        width: parent.width
        color: "#6b686f"
        font.weight: Font.ExtraBold
        font.pixelSize: 15
//        font.family: UIConst.fontname
        //font.family: "sans-serif-light"
    }

    Rectangle {
        id: line
        anchors.top: lblText.bottom
        anchors.topMargin: 1
        height: 1
        width: parent.width
        color: "#c5cccb"
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
