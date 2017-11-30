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
    property var distances: ({});

    function dist(w1, w2){
        return Math.round(Math.sqrt((Math.pow(w2.x-w1.x,2) + Math.pow(w2.y-w1.y,2)))*100)/100;
    }

    function drawLine(ctx, objFrom, objTo){
        ctx.lineWidth = 1;
        ctx.strokeStyle = "red"
        ctx.beginPath()
        ctx.moveTo(objFrom.x, objFrom.y)
        ctx.lineTo(objTo.x, objTo.y)
        ctx.closePath()
        ctx.stroke()
        drawingCanvas.requestPaint();
    }

    function drawCircle(ctx, obj, color){
        ctx.beginPath();
        ctx.fillStyle = color;
        ctx.moveTo(obj.x, obj.y);
        ctx.arc(obj.x, obj.y, 5, 0, Math.PI * 2, false);
        ctx.lineTo(obj.x, obj.y);
        ctx.fill();
    }

    function writeLabel(ctx, objFrom, objTo, label){
        var lblPos = {"x":0,"y":0};
        lblPos.x = (objFrom.x + objTo.x)/2;
        lblPos.y = (objFrom.y + objTo.y)/2;

        ctx.fillStyle = "black";
        ctx.font = "12px sans-serif";
        ctx.fillText(label, lblPos.x, lblPos.y);
        drawingCanvas.requestPaint();
    }

    function addCenter(ctx, obj, radius){
        ctx.beginPath();
        ctx.fillStyle = "blue";
        ctx.moveTo(obj.x, obj.y);
        ctx.arc(obj.x, obj.y, 5, 0, Math.PI * 2, false);
        ctx.lineTo(obj.x, obj.y);
        ctx.fill();
        drawingCanvas.requestPaint();

        ctx.globalAlpha = 0.5;
        ctx.beginPath();
        ctx.strokeStyle = "red"
        ctx.fillStyle = "cyan"
        ctx.moveTo(obj.x, obj.y);
        ctx.arc(obj.x, obj.y, radius, 0, Math.PI * 2, false);
        ctx.lineTo(obj.x, obj.y);
        ctx.fill();

        drawingCanvas.requestPaint();
        ctx.globalAlpha = 1;

    }

    function initAlgorithm(){
        var ctx = drawingCanvas.getContext("2d")
        //For all cities

        var sel_city = Math.floor(Math.random() * cities.length);

        var maxDist = 0;
        var maxDistCity = sel_city;

        for (var j = 0; j < cities.length; j++){
            var distance = dist(cities[j], cities[sel_city]);
            if(distance > maxDist){
                maxDist = distance;
                maxDistCity = j;
            }
        }
        drawLine(ctx, cities[sel_city], cities[maxDistCity]);
        addCenter(ctx, cities[sel_city], maxDist);
        writeLabel(ctx, cities[sel_city], cities[maxDistCity], maxDist);

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
                    initAlgorithm();


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
            var ctx = drawingCanvas.getContext("2d");
            var obj = {"x":mouseX, "y":mouseY};
            drawCircle(ctx, obj, "red");
            drawingCanvas.requestPaint();

            cities.push(obj);
        }
        Path {
            startX: 0; startY: 100
            PathLine { x: 200; y: 100 }
        }
    }
}
