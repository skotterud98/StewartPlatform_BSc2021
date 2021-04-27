import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

PageBackground {
    id: pageBackground
    width: 800
    height: 430
    clip: true
    visible: true

    property alias freqButton: freqButton
    property alias phaseButton: phaseButton
    property alias ampButton: ampButton

    property alias yawSlider: yawSlider
    property alias pitchSlider: pitchSlider
    property alias rollSlider: rollSlider
    property alias heaveSlider: heaveSlider
    property alias swaySlider: swaySlider
    property alias surgeSlider: surgeSlider

    property alias surgeTxt: surgeTxt
    property alias swayTxt: swayTxt
    property alias heaveTxt: heaveTxt
    property alias rollTxt: rollTxt
    property alias pitchTxt: pitchTxt
    property alias yawTxt: yawTxt

    transformOrigin: Item.Center
    title: "Oscillator"

    //Yaw
    Slider {
        id: yawSlider
        objectName: yawSlider
        x: parent.width - 200
        y: parent.height - 280
        width: 259
        height: 50
        stepSize: 0.01
        rotation: 270

        handle: Rectangle {
            x: yawSlider.leftPadding + yawSlider.visualPosition * (yawSlider.availableWidth - width)
            y: yawSlider.topPadding + yawSlider.availableHeight / 2 - height / 2
            color: yawSlider.pressed ? "#f0f0f0" : "#f6f6f6"
            radius: 13
            border.color: "#bdbebf"
            implicitHeight: 26
            implicitWidth: 26
        }
        value: 0
        background: Rectangle {
            x: yawSlider.leftPadding
            y: yawSlider.topPadding + yawSlider.availableHeight / 2 - height / 2
            width: yawSlider.availableWidth
            height: implicitHeight
            color: "#bdbebf"
            radius: 2
            implicitHeight: 4
            Rectangle {
                width: yawSlider.visualPosition * parent.width
                height: parent.height
                color: "#db6221"
                radius: 2
            }
            implicitWidth: 200
        }
    }
    //Pitch
    Slider {
        id: pitchSlider
        objectName: pitchSlider
        x: parent.width - 300
        y: parent.height - 280
        width: 259
        height: 50
        stepSize: 0.01
        layer.smooth: false
        antialiasing: false
        rotation: 270
        handle: Rectangle {
            x: pitchSlider.leftPadding + pitchSlider.visualPosition
               * (pitchSlider.availableWidth - width)
            y: pitchSlider.topPadding + pitchSlider.availableHeight / 2 - height / 2
            color: pitchSlider.pressed ? "#f0f0f0" : "#f6f6f6"
            radius: 13
            border.color: "#bdbebf"
            implicitHeight: 26
            implicitWidth: 26
        }
        value: 0
        background: Rectangle {
            x: pitchSlider.leftPadding
            y: pitchSlider.topPadding + pitchSlider.availableHeight / 2 - height / 2
            width: pitchSlider.availableWidth
            height: implicitHeight
            color: "#bdbebf"
            radius: 2
            implicitHeight: 4
            Rectangle {
                width: pitchSlider.visualPosition * parent.width
                height: parent.height
                color: "#db6221"
                radius: 2
            }
            implicitWidth: 200
        }
    }
    //Roll
    Slider {
        id: rollSlider
        objectName: rollSlider
        x: parent.width - 400
        y: parent.height - 280
        width: 259
        height: 50
        stepSize: 0.01
        rotation: 270
        handle: Rectangle {
            x: rollSlider.leftPadding + rollSlider.visualPosition
               * (rollSlider.availableWidth - width)
            y: rollSlider.topPadding + rollSlider.availableHeight / 2 - height / 2
            color: rollSlider.pressed ? "#f0f0f0" : "#f6f6f6"
            radius: 13
            border.color: "#bdbebf"
            implicitHeight: 26
            implicitWidth: 26
        }
        value: 0
        background: Rectangle {
            x: rollSlider.leftPadding
            y: rollSlider.topPadding + rollSlider.availableHeight / 2 - height / 2
            width: rollSlider.availableWidth
            height: implicitHeight
            color: "#bdbebf"
            radius: 2
            implicitHeight: 4
            Rectangle {
                width: rollSlider.visualPosition * parent.width
                height: parent.height
                color: "#db6221"
                radius: 2
            }
            implicitWidth: 200
        }
    }
    //Heave
    Slider {
        id: heaveSlider
        objectName: heaveSlider
        x: parent.width - 500
        y: parent.height - 280
        width: 259
        height: 50
        stepSize: 0.01
        rotation: 270
        handle: Rectangle {
            x: heaveSlider.leftPadding + heaveSlider.visualPosition
               * (heaveSlider.availableWidth - width)
            y: heaveSlider.topPadding + heaveSlider.availableHeight / 2 - height / 2
            color: heaveSlider.pressed ? "#f0f0f0" : "#f6f6f6"
            radius: 13
            border.color: "#bdbebf"
            implicitHeight: 26
            implicitWidth: 26
        }
        value: 0
        background: Rectangle {
            x: heaveSlider.leftPadding
            y: heaveSlider.topPadding + heaveSlider.availableHeight / 2 - height / 2
            width: heaveSlider.availableWidth
            height: implicitHeight
            color: "#bdbebf"
            radius: 2
            implicitHeight: 4
            Rectangle {
                width: heaveSlider.visualPosition * parent.width
                height: parent.height
                color: "#db6221"
                radius: 2
            }
            implicitWidth: 200
        }
    }
    //Sway
    Slider {
        id: swaySlider
        objectName: swaySlider
        x: parent.width - 600
        y: parent.height - 280
        width: 259
        height: 50
        stepSize: 0.01
        rotation: 270
        handle: Rectangle {
            x: swaySlider.leftPadding + swaySlider.visualPosition
               * (swaySlider.availableWidth - width)
            y: swaySlider.topPadding + swaySlider.availableHeight / 2 - height / 2
            color: swaySlider.pressed ? "#f0f0f0" : "#f6f6f6"
            radius: 13
            border.color: "#bdbebf"
            implicitHeight: 26
            implicitWidth: 26
        }
        value: 0
        background: Rectangle {
            x: swaySlider.leftPadding
            y: swaySlider.topPadding + swaySlider.availableHeight / 2 - height / 2
            width: swaySlider.availableWidth
            height: implicitHeight
            color: "#bdbebf"
            radius: 2
            implicitHeight: 4
            Rectangle {
                width: swaySlider.visualPosition * parent.width
                height: parent.height
                color: "#db6221"
                radius: 2
            }
            implicitWidth: 200
        }
    }
    //Surge
    Slider {
        id: surgeSlider
        objectName: surgeSlider
        x: parent.width - 700
        y: parent.height - 280
        width: 259
        height: 50
        snapMode: Slider.SnapOnRelease
        wheelEnabled: false
        stepSize: 0.01
        rotation: 270
        handle: Rectangle {
            x: surgeSlider.leftPadding + surgeSlider.visualPosition
               * (surgeSlider.availableWidth - width)
            y: surgeSlider.topPadding + surgeSlider.availableHeight / 2 - height / 2
            radius: 13
            border.color: "#bdbebf"
            implicitHeight: 26
            implicitWidth: 26
        }
        value: 0
        background: Rectangle {
            x: surgeSlider.leftPadding
            y: surgeSlider.topPadding + surgeSlider.availableHeight / 2 - height / 2
            width: surgeSlider.availableWidth
            height: implicitHeight
            color: "#bdbebf"
            radius: 2
            implicitHeight: 4
            Rectangle {
                width: surgeSlider.visualPosition * parent.width
                height: parent.height
                color: "#db6221"
                radius: 2
            }
            implicitWidth: 200
        }
    }

    Label {
        id: surgeLabel
        x: 207
        y: 324
        color: "#f6f7f7"
        text: qsTr("SURGE")
        anchors.verticalCenter: surgeSlider.verticalCenter
        anchors.verticalCenterOffset: 140
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        font.bold: true
        font.family: "Ubuntu"
        font.pointSize: 10
    }

    Label {
        id: swayLabel
        x: 311
        y: 324
        color: "#fbfbfb"
        text: qsTr("SWAY")
        anchors.verticalCenter: swaySlider.verticalCenter
        anchors.verticalCenterOffset: 140
        anchors.horizontalCenter: swaySlider.horizontalCenter
        font.bold: true
        font.family: "Arial"
        font.pointSize: 10
    }

    Label {
        id: heaveLabel
        x: 408
        y: 324
        color: "#f9f9f9"
        text: qsTr("HEAVE")
        anchors.verticalCenter: heaveSlider.verticalCenter
        anchors.verticalCenterOffset: 140
        anchors.horizontalCenter: heaveSlider.horizontalCenter
        font.bold: true
        font.family: "Ubuntu"
        font.pointSize: 10
    }

    Label {
        id: rollLabel
        x: 512
        y: 324
        color: "#f6f7f7"
        text: qsTr("ROLL")
        anchors.verticalCenter: rollSlider.verticalCenter
        anchors.verticalCenterOffset: 140
        anchors.horizontalCenter: rollSlider.horizontalCenter
        font.bold: true
        font.family: "Ubuntu"
        font.pointSize: 10
    }

    Label {
        id: pitchLabel
        x: 611
        y: 324
        color: "#f6f7f7"
        text: qsTr("PITCH")
        anchors.verticalCenter: pitchSlider.verticalCenter
        anchors.verticalCenterOffset: 140
        anchors.horizontalCenter: pitchSlider.horizontalCenter
        font.bold: true
        font.family: "Ubuntu"
        font.pointSize: 10
    }

    Label {
        id: yawLabel
        x: 716
        y: 324
        width: 29
        height: 15
        visible: true
        color: "#f4f4f5"
        text: qsTr("YAW")
        anchors.verticalCenter: yawSlider.verticalCenter
        clip: false
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: yawSlider.horizontalCenter
        anchors.verticalCenterOffset: 140
        font.bold: true
        font.family: "Ubuntu"
        font.pointSize: 10
    }

    Switch {
        id: runSW
        x: 45
        y: 256
        width: 95
        height: 52
        text: qsTr("RUN")
    }

    TabButton {
        id: ampButton
        x: 45
        y: 66
        text: qsTr("Amplitude")
        checked: true
        background: Rectangle {
            height: parent.height
            width: parent.width
            color: ampButton.down ? "dimgrey" : "#1a1a1a"
        }
    }

    TabButton {
        id: phaseButton
        x: 45
        y: 120
        text: qsTr("Phase")
        background: Rectangle {
            height: parent.height
            width: parent.width
            color: phaseButton.down ? "dimgrey" : "#1a1a1a"
        }
    }

    TabButton {
        id: freqButton
        x: 45
        y: 174
        text: qsTr("Frequency")
        background: Rectangle {
            height: parent.height
            width: parent.width
            color: freqButton.down ? "dimgrey" : "#1a1a1a"
        }
    }

    Text {
        id: surgeTxt
        x: 218
        y: 20
        color: "#db6221"
        text: qsTr("0")
        anchors.verticalCenter: surgeSlider.verticalCenter
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.NoWrap
        anchors.verticalCenterOffset: -150
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        fontSizeMode: Text.FixedSize
        minimumPixelSize: 12
        font.bold: true
    }

    Text {
        id: swayTxt
        x: 219
        y: 15
        color: "#db6221"
        text: qsTr("0")
        anchors.verticalCenter: surgeSlider.verticalCenter
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.NoWrap
        anchors.verticalCenterOffset: -150
        minimumPixelSize: 12
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        font.bold: true
        anchors.horizontalCenterOffset: 100
        fontSizeMode: Text.FixedSize
    }

    Text {
        id: heaveTxt
        x: 210
        y: 13
        color: "#db6221"
        text: qsTr("0")
        anchors.verticalCenter: surgeSlider.verticalCenter
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.NoWrap
        anchors.verticalCenterOffset: -150
        minimumPixelSize: 12
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        font.bold: true
        anchors.horizontalCenterOffset: 200
        fontSizeMode: Text.FixedSize
    }

    Text {
        id: rollTxt
        x: 212
        y: 25
        color: "#db6221"
        text: qsTr("0")
        anchors.verticalCenter: surgeSlider.verticalCenter
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.NoWrap
        anchors.verticalCenterOffset: -150
        minimumPixelSize: 12
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        font.bold: true
        anchors.horizontalCenterOffset: 300
        fontSizeMode: Text.FixedSize
    }

    Text {
        id: pitchTxt
        x: 209
        y: 26
        color: "#db6221"
        text: qsTr("0")
        anchors.verticalCenter: surgeSlider.verticalCenter
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.NoWrap
        anchors.verticalCenterOffset: -150
        minimumPixelSize: 12
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        font.bold: true
        anchors.horizontalCenterOffset: 400
        fontSizeMode: Text.FixedSize
    }

    Text {
        id: yawTxt
        x: 213
        y: 18
        color: "#db6221"
        text: qsTr("0")
        anchors.verticalCenter: surgeSlider.verticalCenter
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.NoWrap
        anchors.verticalCenterOffset: -150
        minimumPixelSize: 12
        anchors.horizontalCenter: surgeSlider.horizontalCenter
        font.bold: true
        anchors.horizontalCenterOffset: 500
        fontSizeMode: Text.FixedSize
    }
}
