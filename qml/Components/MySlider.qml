import QtQuick 2.0
import QtQuick.Controls 2.12

Slider {
    property string sliderName: qsTr("My Slider")
    property string sliderUnit: qsTr("[ ]")
    property string valueLabel: mySlider.value

    property bool valueVisible: true

    property bool phase: false

    id: mySlider
    width: 260
    height: 50
    rotation: 270
    snapMode: Slider.NoSnap
    stepSize: 1
    from: 0
    to: 50
    handle: Rectangle {
        x: mySlider.leftPadding + mySlider.visualPosition
           * (mySlider.availableWidth - width)
        y: mySlider.topPadding + mySlider.availableHeight / 2 - height / 2
        radius: 13
        border.color: "#bdbebf"
        implicitHeight: 26
        implicitWidth: 26
    }
    background: Rectangle {
        x: mySlider.leftPadding
        y: mySlider.topPadding + mySlider.availableHeight / 2 - height / 2
        width: mySlider.availableWidth
        height: implicitHeight
        color: "#bdbebf"
        radius: 2
        implicitHeight: 4
        Rectangle {
            width: mySlider.visualPosition * parent.width
            height: parent.height
            color: "#db6221"
            radius: 2
        }
        implicitWidth: 200
    }

    Label {
        text: mySlider.sliderName
        color: "#db6221"
        font.bold: true
        rotation: 90
        anchors {
            verticalCenter: mySlider.verticalCenter
            horizontalCenter: mySlider.horizontalCenter
            horizontalCenterOffset: -140
        }
    }

    Text {
        id: myValue
        text: (phase ? Math.round((mySlider.value - 0.5) * 2 * Math.PI * 100) / 100 : Math.round(valueLabel * 100) / 100) + " " + mySlider.sliderUnit
        color: "#db6221"
        font.bold: true
        rotation: 90
        anchors {
            verticalCenter: mySlider.verticalCenter
            horizontalCenter: mySlider.horizontalCenter
            horizontalCenterOffset: 150
        }
        visible: mySlider.valueVisible
    }
}
