import QtQuick 2.12
import QtQuick.Controls 2.12

Switch {
    id: mySwitch
    text: qsTr("My Switch")

    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 26
        x: mySwitch.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: mySwitch.checked ? "#17a81a" : "red"
        border.color: mySwitch.checked ? "#17a81a" : "#cccccc"

        Rectangle {
           x: mySwitch.checked ? parent.width - width : 0
           width: 26
           height: 26
           radius: 13
           color: mySwitch.down ? "#cccccc" : "#ffffff"
           border.color: mySwitch.checked ? (mySwitch.down ? "#17a81a" : "#21be2b") : "#999999"
           opacity: 0.6
        }
    }
    contentItem: Text {
        text: mySwitch.text
        font.bold: true
        color: "#db6221"
        verticalAlignment: Text.AlignVCenter
        leftPadding: mySwitch.indicator.width + mySwitch.spacing
    }
}

