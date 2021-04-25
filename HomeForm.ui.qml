import QtQuick 2.12
import QtQuick.Controls 2.12

PageBackground {
    width: 800
    height: 430
    color: "#1a1a1a"

    title: "Home"

    Rectangle {
        id: rectangle
        x: 294
        y: 140
        width: 145
        height: 45
        color: "#3a3a3a"
    }

    Label {
        id: label
        x: 201
        y: 148
        color: "#db6221"
        text: qsTr("Status:")
        font.pointSize: 15
    }

    Rectangle {
        id: rectangle1
        x: 294
        y: 73
        width: 145
        height: 45
        color: "#3a3a3a"
    }

    Label {
        id: label1
        x: 47
        y: 81
        color: "#db6221"
        text: qsTr("Power Consumption:")
        font.pointSize: 15
    }

    Rectangle {
        id: rectangle2
        x: 294
        y: 206
        width: 145
        height: 45
        color: "#3a3a3a"
    }

    Label {
        id: label2
        x: 187
        y: 214
        color: "#db6221"
        text: qsTr("Current:")
        font.pointSize: 15
    }

    Rectangle {
        id: rectangle3
        x: 294
        y: 277
        width: 145
        height: 45
        color: "#3a3a3a"
    }

    Label {
        id: label3
        x: 127
        y: 285
        color: "#db6221"
        text: qsTr("Placeholder1:")
        font.pointSize: 15
    }

    Image {
        id: image
        x: 110
        y: 368
        width: 581
        height: 54
        source: "pics/Faculty-of-Engineering-and-Science-negative.png"
        fillMode: Image.PreserveAspectFit
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:8}D{i:9}D{i:10}
}
##^##*/
