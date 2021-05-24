import QtQuick 2.15
import QtQuick.Controls 2.15


Page {
    id: mainwindow
    width: 800
    height: 480
    visible: true

    header: ToolBar {
        contentHeight: toolButton.implicitHeight
        background: Rectangle {
            anchors.fill: parent
            color: "#1a1a1a"
        }

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 2.5
            height: 50
            background: Rectangle {
                color: "#3a3a3a"
                opacity: 0.8
            }

            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            font.pixelSize: 25
            font.bold: true
            font.italic: true
            color: "#db6221"
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: mainwindow.width * 0.23
        height: mainwindow.height
        background: Rectangle {
            color: "#1a1a1a"
            anchors.fill: parent
        }
        dragMargin: 0

        Column {
            anchors.fill: parent

            ItemDelegate {
                id: oscillatorDelegate
                text: "Sine Oscillator"
                width: parent.width
                height: 60
                contentItem: Text {
                    text: oscillatorDelegate.text
                    font.italic: true
                    font.bold: true
                    font.pixelSize: 17
                    color: "#db6221"
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: oscillatorDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked: {
                    if(stackView.currentItem.title !== oscillatorDelegate.text)
                        stackView.push("qrc:/qml/SineOscillator.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                id: joystickDelegate
                text: "Joystick"
                width: parent.width
                height: 60
                contentItem: Text {
                    text: joystickDelegate.text
                    font.italic: true
                    font.bold: true
                    font.pixelSize: 17
                    color: "#db6221"
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: joystickDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked: {
                    if(stackView.currentItem.title !== joystickDelegate.text)
                        stackView.push("qrc:/qml/Joystick.qml")
                    drawer.close()
                }
            }
            /*
            ItemDelegate {
                id: waveSimDelegate
                text: "Wave Simulator"
                width: parent.width
                height: 60
                contentItem: Text {
                    text: waveSimDelegate.text
                    font.italic: true
                    font.bold: true
                    font.pixelSize: 17
                    color: "#db6221"
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: waveSimDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked: {
                    if(stackView.currentItem.title !== waveSimDelegate.text)
                        stackView.push("qrc:/qml/WaveSimulator.qml")
                    drawer.close()
                }
            }
            */
            ItemDelegate {
                id: graphsDelegate
                text: "Setpoint Plot"
                width: parent.width
                height: 60
                contentItem: Text {
                    text: graphsDelegate.text
                    font.italic: true
                    font.bold: true
                    font.pixelSize: 17
                    color: "#db6221"
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: graphsDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked: {
                    if(stackView.currentItem.title !== graphsDelegate.text)
                        stackView.push("qrc:/qml/SetpointPlot.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                id: strokePlotDelegate
                text: "Stroke Length"
                width: parent.width
                height: 60
                contentItem: Text {
                    text: strokePlotDelegate.text
                    font.italic: true
                    font.bold: true
                    font.pixelSize: 17
                    color: "#db6221"
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: strokePlotDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked: {
                    if(stackView.currentItem.title !== strokePlotDelegate.text)
                        stackView.push("qrc:/qml/StrokeLength.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                id: infoDelegate
                text: "Info"
                width: parent.width
                height: 60
                contentItem: Text {
                    text: infoDelegate.text
                    font.italic: true
                    font.bold: true
                    font.pixelSize: 17
                    color: "#db6221"
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: infoDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked: {
                    if(stackView.currentItem.title !== infoDelegate.text)
                        stackView.push("qrc:/qml/Info.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "qrc:/qml/Home.qml"
        anchors.fill: parent
    }
}
