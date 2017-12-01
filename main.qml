import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    visible: true
    width: 1280
    height: 756
    title: qsTr("Hello World")

    property var cities: [];
    property var distances: ({});
    property var centers: ({});
    property var c_length: 0;
    property var sel_city: 0;

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

        for(var j=0; j<Object.keys(centers).length; j++){
            console.log(centers[j]);
            drawCircle(ctx, centers.valueOf(j),"blue");
        }
    }

    function findFarthest(ctx, sel_city){
        var maxDistCity = sel_city;
        var maxDist = 0;
        console.log("Citta selezionati " + centers.toString());
        for (var j = 0; j < cities.length; j++){
            if(j in centers){
                console.log("Citta gia presente:" + j);
                continue;
            }

            var distance = dist(cities[j], cities[sel_city]);
            console.log("Distanza: " + distance);
            if(distance > maxDist){
                console.log("Aggiornamento citta piu lontana: " + j);
                maxDist = distance;
                maxDistCity = j;
            }
        }
        console.log("Aggiungo nella lista: " + maxDistCity);

        centers[maxDistCity]={"x":cities[maxDistCity].x, "y":cities[maxDistCity].y};

        drawLine(ctx, cities[sel_city], cities[maxDistCity]);
        addCenter(ctx, cities[sel_city], maxDist);
        writeLabel(ctx, cities[sel_city], cities[maxDistCity], maxDist);
        return maxDistCity;
    }

    function initAlgorithm(){
        var ctx = drawingCanvas.getContext("2d")
        sel_city = Math.floor(Math.random() * cities.length);
        centers[sel_city] = {"x":cities[sel_city].x, "y":cities[sel_city].y};
        console.log("Citta a caso:" + sel_city);
        sel_city = findFarthest(ctx, sel_city);
        c_length = 1;
    }

    function stepOver(){
        var ctx = drawingCanvas.getContext("2d");
        ctx.beginPath();
        ctx.fillStyle = "white";
        ctx.fillRect(0,0,drawingCanvas.width, drawingCanvas.height);

        restoreCanvas();

        if(c_length < k_centers.text){
            sel_city = findFarthest(ctx, sel_city);
            c_length++;
        }else{
            stepBtn.visible = false;
            finishBtn.visible = false;
        }
    }

    function finishAll(){

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
                    initAlgorithm();
                    startBtn.visible = false;
                    stepBtn.visible = true;
                    k_centers.enabled = false;
                    finishBtn.visible = true;
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
        Component.onCompleted: {
            var ctx = drawingCanvas.getContext("2d");
            ctx.beginPath();
            ctx.fillStyle = "white";
            ctx.fill();
            drawingCanvas.requestPaint();
        }

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
