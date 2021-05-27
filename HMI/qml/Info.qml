import QtQuick 2.0
import QtQuick.Controls 2.0
import "Components" as MyComponents


Page {
    width: 800
    height: 430
    title: qsTr("Info")
    MyComponents.BackgroundPage {
        anchors.fill: parent

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: -40
            color: "#db6221"
            text:  "\nConnect keyboard and press ALT + F4 to enter terminal\n\nLogin credentials\nusername:\tpi\npassword:\tstewart123
                    \n\nInfo about sine oscillator mode:\nLive adjustments in a sine wave's frequency, will not take place immediately,
but wait for a zero-point crossing to occur before executing the change.\n\n\nMechatronics BSc. project at the University of Agder, spring 2021"
        }
    }
}
