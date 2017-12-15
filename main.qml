import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2


ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 600
    title: qsTr("Hello World")

    Component.onCompleted: {
        approxFacade.init();
    }

    Dialog {
        id: dialog
        visible: false
        title: "Choose a date"

        function flash(msg){
            dialogText.text = msg;
            dialog.visible = true;
        }

        standardButtons: StandardButton.Ok

        onAccepted: console.log("Saving the date " +
                                calendar.selectedDate.toLocaleDateString())
        Text {
            id: dialogText
            text: "ciao"
        }

    }

    Connections {
        target: approxFacade
        onDataAvailable: {
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
                    //addRadius(ctx, c, r);
                }
            }

            drawingCanvas.requestPaint();
            pbar.visible = false;
        }
        onProgressUpdate: progUpdate(val);
    }

    property var cities: [];
    function progUpdate(val){
        console.log("Val updated");
        pbar.value = val;
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

    function clearCanvas(){
        startBtn.enabled = true
        var width = drawingCanvas.width;
        var height = drawingCanvas.height;
        var ctx = drawingCanvas.getContext("2d");
        ctx.reset();
        cities = []
        approxFacade.init();

        drawingCanvas.requestPaint();
    }

    toolBar:ToolBar {
        RowLayout {
            anchors.fill: parent
            TextField {
                id: k_centers
                //                style: TextFieldStyle {
                //                    textColor: "black"
                //                    background: Rectangle {
                //                        radius: 2
                //                        implicitWidth: 100
                //                        implicitHeight: 24
                //                        border.color: "#333"
                //                        border.width: 1
                //                    }
                //                }
                text: "2"
            }

            ComboBox {
                id: algorithm
                visible: true
                width: 200
                model: [ "2Approx", "Bruteforce"]
            }



            ToolButton {
                id: startBtn
                text: "Resolve"
                onClicked: {
                    if(cities.length > 0){
                        if(k_centers.text > 0){
                            startBtn.enabled = false
                            approxFacade.setCenterCount(k_centers.text);
                            pbar.visible = true;
                            //                    startBtn.visible = false;
                            //                    stepBtn.visible = true;
                            //                    k_centers.enabled = false;
                            //                    finishBtn.visible = true;
                            approxFacade.resolveImmediate(algorithm.currentText);
                        }else{
                            dialog.flash("Impossible run algorithm with 0 centers!");
                        }
                    }else{
                        dialog.flash("City count is not valid");
                    }

                }
            }

            //            ToolButton {
            //                id: stepBtn
            //                visible: false
            //                text: ">>>"
            //                onClicked: {
            //                    console.log("start clicked")
            //                    stepOver();


            //                }
            //            }

            ToolButton {
                id: finishBtn
                visible: false;
                text: "Finish"
                onClicked: {
                    finishAll();
                }
            }

            Item { Layout.fillWidth: true }

            TextField {
                id: city_count
                //                style: TextFieldStyle {
                //                    textColor: "black"
                //                    background: Rectangle {
                //                        radius: 2
                //                        implicitWidth: 100
                //                        implicitHeight: 24
                //                        border.color: "#333"
                //                        border.width: 1
                //                    }
                //                }
                text: "0"
            }
            ToolButton {
                visible: true;
                text: "Random"
                onClicked: {
                    startBtn.enabled = true
                    var width = drawingCanvas.width;
                    var height = drawingCanvas.height;
                    var ctx = drawingCanvas.getContext("2d");
                    ctx.reset();
                    cities = []
                    approxFacade.init();


//                    for(var i=0; i<city_count.text; i++){
//                        var obj = {"x":Math.floor((Math.random() * (width-30)))+15, "y":Math.floor((Math.random() * (height-30)))+15}
//                        approxFacade.setCity(obj.x, obj.y);
//                        cities.push(obj);
//                        drawCircle(ctx, obj, "red");
//                    }




                    var obj = {"x":100, "y":100};
                    drawCircle(ctx, obj, "red");
                    drawingCanvas.requestPaint();

                    cities.push(obj);
                    console.log(approxFacade);
                    approxFacade.setCity(obj.x, obj.y);
                    city_count.text = cities.length



                    obj = {"x":125, "y":100};
                    drawCircle(ctx, obj, "red");
                    drawingCanvas.requestPaint();

                    cities.push(obj);
                    console.log(approxFacade);
                    approxFacade.setCity(obj.x, obj.y);
                    city_count.text = cities.length


                    drawingCanvas.requestPaint();
                }
            }

            ToolButton {
                id: clearBtn
                visible: true;
                text: "Clear"
                onClicked: {

                    clearCanvas();
                }
            }

        }
    }


    ProgressBar {
        id: pbar
        visible: false
        value: 50
        width: parent.width
        minimumValue: 0
        maximumValue: k_centers.text - 1
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
            if(!startBtn.enabled){
                clearCanvas();

            }


            var ctx = drawingCanvas.getContext("2d");

            var obj = {"x":Math.round(mouseX), "y":Math.round(mouseY)};
            drawCircle(ctx, obj, "red");
            drawingCanvas.requestPaint();

            cities.push(obj);
            console.log(approxFacade);
            approxFacade.setCity(Math.round(mouseX), Math.round(mouseY));
            city_count.text = cities.length
        }
    }
}
