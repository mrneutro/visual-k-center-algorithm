import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 600
    title: qsTr("Hello World")

    Component.onCompleted: {
        approxFacade.init();
    }

    property var cities: [];

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

    function addCenter(ctx, obj, color){
        ctx.beginPath();
        ctx.fillStyle = color;
        ctx.moveTo(obj.x, obj.y);
        ctx.arc(obj.x, obj.y, 5, 0, Math.PI * 2, false);
        ctx.lineTo(obj.x, obj.y);
        ctx.fill();
        drawingCanvas.requestPaint();
    }

    function addRadius(ctx, obj, radius){
        ctx.globalAlpha = 0.4;
        ctx.beginPath();
        ctx.lineWidth = 1;
        ctx.strokeColor = "red"
        ctx.strokeStyle = "red"
        ctx.fillStyle = "#3399ff"
        ctx.moveTo(obj.x, obj.y);
        ctx.arc(obj.x, obj.y, radius, 0, Math.PI * 2, false);
        ctx.lineTo(obj.x, obj.y);
        ctx.fill();

        drawingCanvas.requestPaint();
        ctx.globalAlpha = 1;
    }

    function restoreCanvas(){
        var ctx = drawingCanvas.getContext("2d");
        for(var i=0; i<cities.length; i++){
            drawCircle(ctx, cities[i],"red");
        }

        console.log("key: " + JSON.stringify(centers));

        for(var j in centers){
            console.log("OBJ to draw:" + JSON.stringify(centers[j]));
            drawCircle(ctx, centers[j],"blue");
        }
    }

    toolBar:ToolBar {
        RowLayout {
            anchors.fill: parent
            TextField {
                id: k_centers
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
                text: "2"
            }

            ToolButton {
                id: startBtn
                text: "Start"
                onClicked: {
                    approxFacade.setCenterCount(k_centers.text);
                    startBtn.visible = false;
                    stepBtn.visible = true;
                    k_centers.enabled = false;
                    finishBtn.visible = true;
                    approxFacade.resolveImmediate();


                    var ctx = drawingCanvas.getContext("2d");

                    var c1 = {"x":approxFacade.getX(0), "y":approxFacade.getY(0)};
                    var r1 = approxFacade.getR(0);
                    addCenter(ctx, c1, "green");

                    for(var i = 1; i < k_centers.text; i++){
                        console.log("RADIUS is " + approxFacade.getR(i))
                        var c = {"x":approxFacade.getX(i), "y":approxFacade.getY(i)};
                        var r = approxFacade.getR(i);
                        addCenter(ctx, c, "blue");
                        if(k_centers.text-1 != i){
                            addRadius(ctx, c, r);
                        }
                    }

                    drawingCanvas.requestPaint();
                }
            }

            ToolButton {
                id: stepBtn
                visible: false
                text: ">>>"
                onClicked: {
                    console.log("start clicked")
                    stepOver();


                }
            }

            ToolButton {
                id: finishBtn
                visible: false;
                text: "Finish"
                onClicked: {
                    finishAll();
                }
            }

            ToolButton {
                visible: true;
                text: "RAND"
                onClicked: {
                    var width = window.width;
                    var height = window.height;
                    console.log(width);
                    console.log(height);
                    var ctx = drawingCanvas.getContext("2d");
                    for(var i=0; i< 1500; i++){
                        var obj = {"x":Math.floor((Math.random() * (width-10)))+10, "y":Math.floor((Math.random() * (height-10)))+10};
                        approxFacade.setCity(obj.x, obj.y);
                        drawCircle(ctx, obj, "red");
                    }
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
            var ctx = drawingCanvas.getContext("2d");
            var obj = {"x":Math.round(mouseX), "y":Math.round(mouseY)};
            drawCircle(ctx, obj, "red");
            drawingCanvas.requestPaint();

            cities.push(obj);
            console.log(approxFacade);
            approxFacade.setCity(Math.round(mouseX), Math.round(mouseY));
        }
        Path {
            startX: 0; startY: 100
            PathLine { x: 200; y: 100 }
        }
    }
}
