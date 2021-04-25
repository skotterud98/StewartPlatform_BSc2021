import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 480

    header: ToolBar {
        contentHeight: toolButton.height
        background: Rectangle
        {
            height: parent.height
            color: "#1a1a1a"
        }

        ToolButton
        {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 2
            height: 50
            background: Rectangle
            {
                color: "#1a1a1a"
            }

            onClicked: {
                if (stackView.depth > 1)
                {
                    stackView.pop()
                }
                else
                {
                    drawer.open()
                }
            }
        }

        Label
        {
            text: stackView.currentItem.title
            anchors.centerIn: parent
            color: "#db6221"
        }
    }

    Drawer
    {
        id: drawer
        width: window.width * 0.15
        height: window.height
        background: Rectangle
        {
            color: "#1a1a1a"
        }

        Column
        {
            anchors.fill: parent

            ItemDelegate
            {
                id: oscillatorDelegate
                text: qsTr("Oscillator")
                width: parent.width
                contentItem: Text {
                    text: oscillatorDelegate.text
                    color: "#db6221"
                }
                background: Rectangle {
                    height: parent.height
                    width: parent.width
                    color: oscillatorDelegate.down ? "dimgrey" : "#1a1a1a"
                }

                onClicked:
                {
                    stackView.push("Oscillator.qml")
                    drawer.close()
                }
            }
            ItemDelegate
            {
                text: qsTr("Page 2")
                width: parent.width
                onClicked:
                {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView
    {
        id: stackView
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }
}











