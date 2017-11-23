import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property var cities: [];

    function dist(w1, w2){
        return Math.sqrt((w2.x-w1.x)^2 + (w2.y-w1.y)^2);
    }

    function drawDistance(x1,y1,x2,y2){

    }

    toolBar:ToolBar {
        RowLayout {
            anchors.fill: parent
            TextField {
                style: TextFieldStyle {
                    textColor: "black"
                    background: Rectangle {
                        radius: 2
                        implicitWidth: 100
                        implicitHeight: 24
                        border.color: "#333"
                        border.width: 1
                    }
                }
                text: "0"
            }

            ToolButton {
                text:"Start"
                onClicked: {
                    console.log("start clicked")
                    var component = Qt.createComponent("line-distance.qml");
                    var object = component.createObject(canvasid);

                    var ctx = drawingCanvas.getContext("2d")
                    ctx.lineWidth = 3;
                    ctx.strokeStyle = "red"
                    ctx.beginPath()
                    console.log("Citi 1"+ cities[0].x +" "+ cities[0].y)
                    ctx.moveTo(Math.round(cities[0].x), Math.round(cities[0].y))
                    ctx.lineTo(cities[1].x, cities[1].y)
                    ctx.closePath()
                    ctx.stroke()
                    drawingCanvas.requestPaint();
                }
            }

            Item { Layout.fillWidth: true }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
        }
    }

    Canvas {
        id: drawingCanvas
        anchors.fill: parent
        onPaint: {

        }
    }

    MouseArea {
        id: canvasid
        anchors.fill: parent
        onClicked: {
            var component = Qt.createComponent("city.qml");
            var object = component.createObject(parent);
            object.y = mouseY;
            object.x = mouseX;
            cities.push(object);

        }
        Path {
            startX: 0; startY: 100
            PathLine { x: 200; y: 100 }
        }
    }
}
