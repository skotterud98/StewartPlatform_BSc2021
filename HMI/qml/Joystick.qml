import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import "Components" as MyComponents

// Joystick QML object taken from "aaronsnoswell" on GitHub
// https://github.com/aaronsnoswell/QMLVirtualJoystick?fbclid=IwAR1CwyLd1wGTuJ3gjLTFb5s5LBaEb3n1GItlDEhfWlu6XChkqjMW99Gq1E8

Page {
    width: 800
    height: 430
    title: "Joystick"
    MyComponents.BackgroundPage {
        anchors.fill: parent

        StatusIndicator {
            id: statusInd
            x: 650
            y: 370
            active: true
            color: _controller.runningProgram == "Joystick" ? "green" : "red"
        }
        Text {
            id: statusIndText
            x: 700
            y: 380
            text: qsTr("Active")
            color: "#db6221"
            font.bold: true
        }
        MyComponents.MySlider {
            id: responseSlider; sliderName: qsTr("RESPONSE"); x: -50; y: parent.height - 265
            from: 0.1; to: 1; stepSize: 0.1; value: _joystick.response; valueVisible: false

            onMoved: _joystick.response = responseSlider.value
        }
        MyComponents.MySlider {
            id: maxAngleSlider; sliderName: qsTr("RANGE"); x: 100; y: parent.height - 265; sliderUnit: "deg"; from: 1
            to: 20; stepSize: 1; value: _joystick.range

            onMoved: _joystick.range = maxAngleSlider.value
        }
        Image {
            id: joystick

            property real angle : 0
            property real distance : 0

            source: "qrc:/qml/images/joyBackground.png"
            anchors.verticalCenterOffset: -30
            anchors.horizontalCenterOffset: 150
            anchors.centerIn: parent
            width: parent.width / 2.3
            height: joystick.width

            ParallelAnimation {
                id: returnAnimation
                NumberAnimation { target: thumb.anchors; property: "horizontalCenterOffset";
                    to: 0; duration: 200; easing.type: Easing.OutSine }
                NumberAnimation { target: thumb.anchors; property: "verticalCenterOffset";
                    to: 0; duration: 200; easing.type: Easing.OutSine }
            }
            MouseArea {
                id: mouse
                signal joystick_moved(double x, double y);

                onJoystick_moved: {
                    _joystick.joyX = x
                    _joystick.joyY = y
                }
                property real fingerAngle : Math.atan2(mouseX, mouseY)
                property int mcx : mouseX - width * 0.5
                property int mcy : mouseY - height * 0.5
                property bool fingerInBounds : fingerDistance2 < distanceBound2
                property real fingerDistance2 : mcx * mcx + mcy * mcy
                property real distanceBound : width * 0.5 - thumb.width * 0.5
                property real distanceBound2 : distanceBound * distanceBound

                property double signal_x : (mouseX - joystick.width/2) / distanceBound
                property double signal_y : -(mouseY - joystick.height/2) / distanceBound

                anchors.fill: parent
                anchors.bottomMargin: 0
                anchors.rightMargin: 0
                anchors.topMargin: 0

                onPressed: {
                    returnAnimation.stop();
                }

                onReleased: {
                    returnAnimation.restart()
                    joystick_moved(0, 0);
                }

                onPositionChanged: {
                    if (fingerInBounds) {
                        thumb.anchors.horizontalCenterOffset = mcx
                        thumb.anchors.verticalCenterOffset = mcy
                    } else {
                        var angle = Math.atan2(mcy, mcx)
                        thumb.anchors.horizontalCenterOffset = Math.cos(angle) * distanceBound
                        thumb.anchors.verticalCenterOffset = Math.sin(angle) * distanceBound
                    }

                    angle = Math.atan2(signal_y, signal_x)

                    if(fingerInBounds) {
                        joystick_moved(
                            Math.cos(angle) * Math.sqrt(fingerDistance2) / distanceBound,
                            Math.sin(angle) * Math.sqrt(fingerDistance2) / distanceBound
                        );
                    } else {
                        joystick_moved(
                            Math.cos(angle) * 1,
                            Math.sin(angle) * 1
                        );
                    }
                }
            }
            Image {
                id: thumb
                source: "qrc:/qml/images/joyFinger.png"
                anchors.centerIn: parent
            }
        }
    }
}


