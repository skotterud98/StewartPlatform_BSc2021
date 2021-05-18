import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.1
import "Components" as Components


Page {
    width: 800
    height: 430
    title: "Stewart Platform"
    Components.BackgroundPage {
        anchors.fill: parent

        ComboBox {
            id: programComboBox

            property string m_program: "Park"

            width: 200
            height: 40
            x: 45
            y: 66
            currentIndex: 0
            model: ["Park", "Neutral", "Sine Oscillator", "Joystick", "JONSWAP"]

            background: Rectangle {
                id: background
                anchors.fill: parent
                color: "dimgrey"
                opacity: 0.8
                radius: 5
            }
            contentItem: Text {
                id: text
                font.pixelSize: 18
                text: programComboBox.currentText
                color: "#db6221"
                font.bold: true
                anchors.horizontalCenter: programComboBox.horizontalCenter
                anchors.verticalCenter: programComboBox.verticalCenter
                anchors.verticalCenterOffset: 10
            }
        }

        Text {
                id: selectorLabel
                text: "Select Mode"
                color: "#db6221"
                font.bold: true
                anchors {
                    verticalCenter: programComboBox.verticalCenter
                    horizontalCenter: programComboBox.horizontalCenter
                    verticalCenterOffset: -45
                }

        }

        Text {
            id: choiceErr
            x: 45
            y: 180
            text: "Enter 'Neutral' first"
            color: "#ff0000"
            font.bold: true
            visible: false
        }

        Components.MyButton {
            id: confirmProgramButton
            x: 45
            y: 120
            text: "Confirm choice"
            onClicked: {

                if (programComboBox.m_program === "Park" && programComboBox.currentText !== "Neutral") { choiceErr.visible = true }
                else if (programComboBox.currentText !== programComboBox.m_program)
                {
                    programComboBox.m_program = programComboBox.currentText
                    _controller.setProgram(programComboBox.currentText)
                    choiceErr.visible = false
                }
            }
        }

        Components.MyButton {
            id: activateButton
            x: 45
            y: 230
            text: "Activate"
            onClicked: _controller.activated = true
        }
        Components.MyButton {
            id: deactivateButton
            x: 150
            y: 230
            text: "Deactivate"
            onClicked: _controller.activated = false
        }

        Text {
            id: status
            x: 45
            y: 290
            text: "Platform Status:"
            color: "#db6221"
            font.bold: true
        }

        Text {
            id: activeText
            x: 220
            y: 290
            text: _controller.activated ? "ACTIVE" : "INACTIVE"
            color: _controller.activated ? "#228b22" : "#ff0000"
            font.bold: true
            visible: true
        }

        Text {
            id: program
            x: 45
            y: 330
            text: "Mode:"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: programText
            x: 130
            y: 330
            text: programComboBox.m_program
            color: "#1e90ff"
            font.bold: true
            visible: true
        }

        Text {
            id: canbusTX
            x: 450
            anchors.verticalCenter: selectorLabel.verticalCenter
            text: "CAN-bus Tx:"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: canbusTxText
            x: 600
            anchors.verticalCenter: selectorLabel.verticalCenter
            text: _controller.activated ? "TRANSMITTING" : "INACTIVE"
            color: {
                if (canbusTxText.text === "TRANSMITTING")
                    "#228b22"
                else if (canbusTxText.text === "INACTIVE")
                    "#ffd700"
            }

            font.bold: true
            visible: true
        }

        Text {
            id: canbusRX
            x: 450
            anchors.verticalCenter: programComboBox.verticalCenter
            text: "CAN-bus Rx:"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: canbusRxText
            x: 600
            anchors.verticalCenter: programComboBox.verticalCenter
            text: _controller.canReadState && _controller.activated ? "RECEIVING" : _controller.activated ? "ERROR" : "PENDING"
            color: {
                if (canbusRxText.text === "RECEIVING")
                    "#228b22"
                else if (canbusRxText.text === "PENDING")
                    "#ffd700"
                else if (canbusRxText.text == "ERROR")
                    "#ff0000"
            }

            font.bold: true
            visible: true
        }

        Text {
            id: ampere
            x: 450
            anchors.verticalCenter: confirmProgramButton.verticalCenter
            text: "12V current: "
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: ampereText
            x: 600
            anchors.verticalCenter: confirmProgramButton.verticalCenter
            text: _controller.activated ? _controller.ampere / 100 + "  A" : "--- A"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Image {
            id: stewart
            width: parent.width / 2.3
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
                horizontalCenterOffset: 120
                verticalCenterOffset: 50
            }
            opacity: 0.5
            fillMode: Image.PreserveAspectFit
            source: "qrc:/qml/images/uia1.png"
        }

        Components.MyButton {
            id: shutdownButton
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
                horizontalCenterOffset: 300
                verticalCenterOffset: 150
            }
            text: "Shutdown"
            onClicked: shutdownMessage.visible = true
        }

        MessageDialog {
            id: shutdownMessage
            title: "Shutdown"
            icon: StandardIcon.Question
            text: programComboBox.m_program === "Park" ? "Are you sure you want to shut off platform?" : "Park actuators!"
            standardButtons: programComboBox.m_program === "Park" ? StandardButton.No | StandardButton.Yes : StandardButton.Close
            visible: false
            onYes: _controller.shutdown()
        }
    }
}


