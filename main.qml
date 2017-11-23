import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MouseArea {
        anchors.fill: parent
        onClicked: {
            var component = Qt.createComponent("city.qml");
            var object = component.createObject(parent);
            object.x = mouseX;
            object.y = mouseY;
        }
    }

    Rectangle {
        x:20
        y:20
        color: "red"
        radius: width*0.5
        height: width
        width: 10
    }
}
