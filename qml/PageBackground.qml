import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Rectangle {
     Material.theme: Material.Dark
     Material.accent: Material.DeepOrange
     width: 800
     height: 430
     color: "#1a1a1a"
     clip: true
     property alias title: label.text

     Label {
         id: label
         x: 618
         y: 8
         width: 130
         height: 36
         color: "#f46210"
         text: qsTr("SP GUI")
         font.family: "Arial"
         styleColor: "#ee1111"
         font.pointSize: 21
         visible: false
     }
     Rectangle {
         id: rectangle1
         x: -86
         y: 368
         width: 100
         height: 200
         color: "#3a3a3a"
         rotation: 45
     }
     Rectangle {
         id: rectangle3
         x: 786
         y: 368
         width: 100
         height: 200
         color: "#3a3a3a"
         rotation: 135
     }
}
