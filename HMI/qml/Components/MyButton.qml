import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: myButton
    text: qsTr("Button")

    background: Rectangle {
        id: myBackground
        height: parent.height
        width: parent.width
        color: myButton.pressed ? "dimgrey" : "#3a3a3a"
        opacity: 0.8
        radius: 5
    }

    contentItem: Text {
        text: myButton.text
        color: "#db6221"
        font.bold: true
    }
}
