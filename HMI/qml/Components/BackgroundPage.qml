import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Rectangle {
    id: background
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange
    color: "#1a1a1a"
    
    Rectangle {
        id: cornerLeft
        x: -86
        y: 368
        width: 100
        height: 200
        color: "#3a3a3a"
        opacity: 0.8
        rotation: 45
    }
    
    Rectangle {
        id: cornerRight
        x: 786
        y: 368
        width: 100
        height: 200
        color: "#3a3a3a"
        opacity: 0.8
        rotation: 135
    }

    Image {
        id: uia
        width: parent.width / 2.5
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 10
        }
        opacity: 0.6
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qml/images/Faculty-of-Engineering-and-Science-negative.png"
    }
}
