import QtQuick 2.0
import QtQuick.Controls 2.0

TabButton {
    id: tabButton
    text: qsTr("TabButton")
    background: Rectangle {
        height: parent.height
        width: parent.width
        color: tabButton.checked ? "#3a3a3a" : "#1a1a1a"
        opacity: 0.8
        radius: 5
    }
    contentItem: Text {
        text: tabButton.text
        color: "#db6221"
        font.bold: true
    }
}
