import QtQuick 2.0
import QtQuick.Controls 2.0
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
                text: "Select Program"
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
                else if (programComboBox.m_program !== "Park" && programComboBox.currentText === "Neutral") { /* Pass */ }
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
            text: "Status:"
            color: "#db6221"
            font.bold: true
        }

        Text {
            id: activeText
            x: 130
            y: 290
            text: _controller.activated ? "ACTIVATED" : "DEACTIVATED"
            color: _controller.activated ? "#228b22" : "#ff0000"
            font.bold: true
            visible: true
        }

        Text {
            id: program
            x: 45
            y: 330
            text: "Program:"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: programText
            x: 150
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
            text: "CAN-bus TX:"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: canbusTxText
            x: 600
            anchors.verticalCenter: selectorLabel.verticalCenter
            text: _controller.activated ? "TRANSMITTING" : "PENDING"
            color: {
                if (canbusTxText.text === "TRANSMITTING")
                    "#228b22"
                else if (canbusTxText.text === "PENDING")
                    "#ffd700"
            }

            font.bold: true
            visible: true
        }

        Text {
            id: canbusRX
            x: 450
            anchors.verticalCenter: programComboBox.verticalCenter
            text: "CAN-bus RX:"
            color: "#db6221"
            font.bold: true
            visible: true
        }

        Text {
            id: canbusRxText
            x: 600
            anchors.verticalCenter: programComboBox.verticalCenter
            text: "PENDING"
            color: {
                if (canbusRxText.text === "TRANSMITTING")
                    "#228b22"
                else if (canbusRxText.text === "PENDING")
                    "#ffd700"
            }

            font.bold: true
            visible: true
        }
    }
}


