import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    id: matBtn
    signal clicked()
    property alias text: innerBtn.text
    property alias enabled: innerBtn.enabled
    property alias button: innerBtn
    property string style: "blue"

    Button {
        id: innerBtn
        text: "Button"
        anchors.fill: parent
        onClicked:{
            matBtn.clicked()
        }

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100*scaleFactor
                implicitHeight: 55*scaleFactor
                border.width: control.activeFocus ? 2 : 1
                radius: 4*scaleFactor
                color: matBtn.style == "blue" ? (control.enabled ? "#3694c4" : "#9fa09a") : (control.enabled ? "#cbcece" : "#9fa09a")
                border.color: "transparent"
            }
            label: Component {
                Text {
                    text: innerBtn.text
                    clip: true
                    color: matBtn.style === "blue" ? "white" : "black"
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    anchors.margins: 5*scaleFactor
                    //font.bold: true
                    font.weight: Font.DemiBold
                    font.capitalization: Font.AllUppercase
                    font.pixelSize: 12   * scaleFactor
                    font.family: UIConst.fontname
                }
            }
        }
    }

    DropShadow {
        id: shadowEff
        visible: Qt.platform.os != "ios"
        anchors.fill: innerBtn
        horizontalOffset: 0
        spread: 0
        verticalOffset: innerBtn.pressed ? 4*scaleFactor : 2*scaleFactor
        radius: 1 * scaleFactor
        samples: 7
        color: "#30000000"
        source: innerBtn
    }
}

