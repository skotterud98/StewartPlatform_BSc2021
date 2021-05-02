import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: myButton
    text: qsTr("Button")

    background: Rectangle {
        height: parent.height
        width: parent.width
        color: myButton.pressed ? "dimgrey" : "#1a1a1a"
        opacity: 0.3
        radius: 5
    }

    contentItem: Text {
        text: myButton.text
        color: "#db6221"
        font.bold: true
    }
}
