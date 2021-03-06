import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2


ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Metric k-center solver")

    property int lastVal: 0

    Connections {
        target: approxFacade
        onDataAvailable: {
            var ctx = drawingCanvas.getContext("2d");

            var point_color = (algorithm.currentIndex==0)?"blue":"black";

            var c1 = {"x":approxFacade.getX(0), "y":approxFacade.getY(0)};
            var r1 = approxFacade.getR(0);
            addCenter(ctx, c1, point_color);

            for(var i = 1; i < k_centers.text; i++){
                console.log("RADIUS is " + approxFacade.getR(i))
                var c = {"x":approxFacade.getX(i), "y":approxFacade.getY(i)};
                var r = approxFacade.getR(i);
                addCenter(ctx, c, point_color);
                if(k_centers.text-1 != i){
                    //addRadius(ctx, c, r);
                }
            }

            drawingCanvas.requestPaint();
            stateId.state = "results"
            var time = approxFacade.last_execution_time();
            outTxt.append("Exec time: " + time + " sec.");
            if(algorithm.currentIndex == 0){
                outTxt.append("Sol. qual.:" + approxFacade.solution_quality());
            }else{
                outTxt.append("Sol. qual.:" + approxFacade.solution_quality() +"(+ max "+approxFacade.getPrecitionDensity()+"px err)");
            }

            //execTime.text = "Time: " + time +" sec.";

        }
        onProgressUpdate: progUpdate(val);
        onProgressMaxVal: progMax(val);
    }
    Connections {
        target: approxFacade
        onError: errorHandle(err)
        onDrawLine: drawLineXY(x, y, toX, toY)
    }

    function drawLineXY(x, y, toX, toY){
        console.log("Drawing line from "+x+" "+y+" to "+toX +" "+toY)
        var ctx = drawingCanvas.getContext("2d");
        ctx.lineWidth = 1;
        ctx.strokeStyle = "green"
        ctx.beginPath()
        ctx.moveTo(x,y)
        ctx.lineTo(toX, toY)
        ctx.closePath()
        ctx.stroke()
        drawingCanvas.requestPaint();
    }

    function errorHandle(err){
        approxFacade.stop();
        stateId.state = "results"
        messageDialog.text = err;
        messageDialog.visible = true
    }

    MessageDialog {
        id: messageDialog
        title: "Error"
        text: "It's so cool that you are using Qt Quick."
        onAccepted: {
            console.log("And of course you could only agree.")
            messageDialog.close()
        }
    }

    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            var calcpersec = pbar.value - lastVal;
            lastVal = pbar.value;
            progressSpeed.text = "Calc per sec: "+ calcpersec;
            var timeinsec = (pbar.maximumValue-pbar.value)/calcpersec;
            console.log(timeinsec);

            if(timeinsec > 60*60*24*365*1000){
                estimatedTime.text = "Est. time: " + Math.round(timeinsec/60*60*24*365*1000) +" millenni";
            }else if(timeinsec > 60*60*24*365){
                estimatedTime.text = "Est. time: " + Math.round(timeinsec/60*60*24*365) +" anni";
            }else if(timeinsec > 60*60*24){
                estimatedTime.text = "Est. time: " + Math.round(timeinsec/60*60*24) +" giorni";
            }else if(timeinsec > 60*60){
                estimatedTime.text = "Est. time: " + Math.round(timeinsec/60*60) +" ore";
            }else if(timeinsec > 60){
                estimatedTime.text = "Est. time: " + Math.round(timeinsec/60) +" min";
            }else{
                estimatedTime.text = "Est. time: " + Math.round(timeinsec) +" sec";
            }


        }
    }

    property var cities: [];

    function exportCities(){
        var obj = {"w":window.width, "h":window.height, "c":cities};
        return JSON.stringify(obj);
    }

    function importCities(str){
        var obj = JSON.parse(str);
        window.width = obj.w;
        window.height = obj.h;
        clearCanvas();
        cities = obj.c;
        cities.forEach(function(element) {
            console.log(element);
            approxFacade.setCity(element.x, element.y);
        });
        restoreCanvas();
    }

    function progUpdate(val){
        pbar.value = val;
        progressTxt.text = val + "/" + pbar.maximumValue
    }

    function progMax(val){
        pbar.maximumValue = val;
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
        ctx.arc(obj.x, obj.y, 4, 0, Math.PI * 2, false);
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
        ctx.arc(obj.x, obj.y, 4, 0, Math.PI * 2, false);
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
        var width = drawingCanvas.width;
        var height = drawingCanvas.height;
        var ctx = drawingCanvas.getContext("2d");
        ctx.reset();
        cities = []
        approxFacade.init();

        drawingCanvas.requestPaint();
    }

    function generateRandomCities(count){
        var width = drawingCanvas.width;
        var height = drawingCanvas.height;
        var ctx = drawingCanvas.getContext("2d");


        for(var i=0; i<count; i++){
            var obj = {"x":Math.floor((Math.random() * (width-30)))+15, "y":Math.floor((Math.random() * (height-30)))+15}
            approxFacade.setCity(obj.x, obj.y);
            cities.push(obj);
            drawCircle(ctx, obj, "red");
        }

        drawingCanvas.requestPaint();
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

    Dialog {
        id: randomDialog
        visible: false
        title: "Choose random cities count"

        standardButtons: StandardButton.Ok | StandardButton.Cancel

        onAccepted: {
            generateRandomCities(randomDialogTxt.text)
        }

        onRejected: visible = false
        RowLayout {
            Text{
                text: "Random cities count: "
            }
            TextField {
                id: randomDialogTxt
                text: "1"
            }
        }

    }

    Dialog {
        id: dencityDialog
        visible: false
        title: "Choose dencity for random generation"

        standardButtons: StandardButton.Ok | StandardButton.Cancel

        onAccepted: {
            dencityDialogTxt.text
            generateRandomCities(window.width*window.height*(dencityDialogTxt.text/100));
        }

        onRejected: visible = false
        RowLayout {
            Text{
                text: "Dencity of cities: "
            }
            TextField {
                id: dencityDialogTxt
                text: "1"
            }
        }

    }

    Dialog {
        id: importDialog
        visible: false
        title: "Choose random cities count"

        standardButtons: StandardButton.Ok

        onAccepted: {
            importCities(importDialogTxt.text)
        }

        RowLayout {
            Text{
                text: "Import hash:"
            }
            TextArea {
                id: importDialogTxt
                text: ""
            }
        }

    }

    Dialog {
        id: exportDialog
        visible: false
        title: "Choose random cities count"

        standardButtons: StandardButton.Ok

        onAccepted: {
            visible=false;
        }

        RowLayout {
            Text{
                text: "Hash:"
            }
            TextArea {
                id: exportDialogTxt
                text: ""
            }
        }

    }


    Component.onCompleted: {
        approxFacade.init();
        stateId.state = "config"
        algorithm.currentIndex=1
    }

    Item {
        id: stateId
        states: [
            State {
                name: "config"
            },
            State {
                name: "working"
            },
            State {
                name: "results"
            }
        ]
    }

    Row {

        id: mainPan
        width: 600
        height: 600

        Canvas {
            id: drawingCanvas
            width: 600
            height: 600

            onPaint: {

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
                    approxFacade.setCity(Math.round(mouseX), Math.round(mouseY));
                    city_count.text = cities.length
                }
            }
        }


    }

    Rectangle {
        anchors.right: separatorPan.left
        height: 600
        width: 2
        color: "#c9ddfc"
    }

    Rectangle {
        id: separatorPan
        anchors.right: configPan.left
        height: 600
        width: 7
        color: "white"
    }

    Rectangle {
        id: configPan
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 200
        height: 600

        ColumnLayout {
            anchors.topMargin: 50
            anchors.leftMargin: 50

            UnderlinedText {
                title: "Configuration"
            }

            Rectangle {
                id: settingsPan
                height: 50
                color:"blue"
                width: childrenRect.width

                GridLayout {
                    columns: 2
                    anchors.fill: parent

                    Text {
                        text: "Centers:"
                    }
                    TextField {
                        id: k_centers
                        text: "2"
                        Layout.preferredWidth: 40
                        enabled: stateId.state == "config"
                    }

                    Text{
                        text: "Algorithm:"
                    }

                    ComboBox {
                        id: algorithm
                        visible: true
                        width: 100
                        model: [ "2Approx", "Bruteforce"]
                        enabled: stateId.state == "config" || stateId.state == "results"
                    }

                    Text{
                        id: precisionLbl
                        text: "Precision:"
                        visible: algorithm.currentIndex==1
                    }

                    TextField {
                        id: precisionTxt
                        text: "2"
                        visible: algorithm.currentIndex==1
                        Layout.preferredWidth: 40
                        enabled: stateId.state == "config" || stateId.state == "results"
                    }
                }

            }

            Item {
                id: spacer1
                anchors.top: settingsPan.bottom
                width: 100
                height: 35
            }

            UnderlinedText {
                id: settingsTitle
                anchors.top: spacer1.bottom
                title: "Utilities"
            }

            RowLayout {
                id: optionsGroup
                Button {
                    id: clearBtn
                    visible: true;
                    implicitWidth: 92
                    text: "Clear"
                    enabled: stateId.state == "config" || stateId.state == "results"
                    onClicked: {
                        clearCanvas();
                        stateId.state = "config"
                    }
                }

                Button {
                    id: randomBtn
                    visible: true
                    implicitWidth: 92
                    text: "Random"
                    enabled: stateId.state == "config" || stateId.state == "results"
                    onClicked: {
                        randomDialog.visible = true
                    }
                }
            }

            RowLayout {
                id: options2Group
                Button {
                    id: exportBtn
                    visible: true
                    implicitWidth: 92
                    text: "Export"
                    enabled: stateId.state == "config" || stateId.state == "results"
                    onClicked: {
                        exportDialogTxt.text = exportCities();
                        exportDialog.visible=true;
                    }
                }

                Button {
                    id: importBtn
                    visible: true
                    implicitWidth: 92
                    text: "Import"
                    enabled: stateId.state == "config" || stateId.state == "results"
                    onClicked: {
                        importDialog.visible=true;
                    }
                }
            }

            Button {
                id: dencityBtn
                visible: true
                implicitWidth: 190
                text: "Fill with dencity"
                enabled: stateId.state == "config" || stateId.state == "results"
                onClicked: {
                    dencityDialog.visible = true
                }
            }

            Item {
                id: spacer2
                anchors.top: optionsGroup.bottom
                width: 100
                height: 64
            }

            UnderlinedText {
                id: runningTitle
                anchors.top: spacer2.bottom
                title: "Run"
            }

            ColumnLayout {
                id: runningGroup
                anchors.topMargin: 10
                anchors.top: runningTitle.bottom


                Button {
                    id: startBtn
                    text: "Resolve immediate"
                    implicitWidth: 190
                    enabled: stateId.state == "config" || stateId.state == "results"

                    onClicked: {
                        if(cities.length > 0){
                            if(k_centers.text > 0){
                                outTxt.append("==START " + algorithm.currentText + "==");
                                stateId.state = "working"
                                approxFacade.setCenterCount(k_centers.text);
                                var real = Number(precisionTxt.text)
                                approxFacade.setPrecision(real);
                                approxFacade.resolveImmediate(algorithm.currentText);

                            }else{
                                dialog.flash("Impossible run algorithm with 0 centers!");
                            }
                        }else{
                            dialog.flash("City count is not valid");
                        }

                    }
                }

                Button {
                    id: startBtnSbS
                    text: "Resolve step-by-step"
                    implicitWidth: 190
                    enabled: stateId.state == "config"
                    visible: false
                }

                ProgressBar {
                    id: pbar
                    visible: stateId.state == "working"

                    implicitWidth: 190


                    Text {
                        id: progressTxt
                        text: "";
                        color: "black"
                        anchors.centerIn: parent
                    }

                }

                Button {
                    id: stopBtn
                    visible: stateId.state == "working"
                    text: "STOP"
                    implicitWidth: 190

                    onClicked: {
                        approxFacade.stop();
                        stateId.state = "results"
                    }

                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 25
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "#ff3a3a" : "#ff5b5b" }
                                GradientStop { position: 1 ; color: control.pressed ? "#ff5b5b" : "#ff3a3a" }
                            }
                        }
                    }
                }
            }

            Item {
                id: spacer3
                anchors.top: runningGroup.bottom
                width: 100
                height: 10
            }

            UnderlinedText {
                id: statisticTitle
                anchors.top: spacer3.bottom
                title: "Statistic"
            }

            Text{
                id: progressSpeed
                text: "Calc per sec: ";
            }

            Text{
                id: estimatedTime
                text: "Est. time: ";
            }

            TextArea {
                id: outTxt
                implicitWidth: 190
                anchors.bottom: parent.bottom
                text:""
            }

        }
    }
}
