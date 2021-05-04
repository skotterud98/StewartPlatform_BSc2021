import QtQuick 2.0
import QtQuick.Controls 2.0
import QtCharts 2.3
import "Components" as MyComponents


Page {
    width: 800
    height: 430
    title: "Stroke Length"
    MyComponents.BackgroundPage {
        anchors.fill: parent

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -40
            height: 400
            width: 800
            color: "transparent"

            ChartView {
                id: strokeChart
                anchors.fill: parent
                legend.alignment: Qt.AlignRight
                animationOptions: ChartView.NoAnimation
                antialiasing: true
                backgroundColor: "#1a1a1a"

            }
        }

        Timer {
            id: timer
            interval: 100
            running: true
            repeat: true
            triggeredOnStart: false

            onTriggered: {
                var stroke = strokeChart.series("Actuators")

                if (!stroke) {
                    stroke = strokeChart.createSeries(ChartView.SeriesTypeBar, "Actuators")

                    strokeChart.axisY().min = 0
                    strokeChart.axisY().max = 90
                    strokeChart.axisY().tickCount = 10
                    strokeChart.axisY().titleText = "Stroke [mm]"
                    strokeChart.axisY().gridVisible = false
                    strokeChart.axisY().labelFormat = "%.0f"

                    strokeChart.axisX().categories = ["Act 1", "Act 2", "Act 3", "Act 4", "Act 5", "Act 6"]
                    strokeChart.axisX().label = ["Ref", "Feedback"]


                }

                var act1 = _controller.strokeRef[0]
                var act2 = _controller.strokeRef[1]
                var act3 = _controller.strokeRef[2]
                var act4 = _controller.strokeRef[3]
                var act5 = _controller.strokeRef[4]
                var act6 = _controller.strokeRef[5]

                if (act1 > 89. || act1 < 1. || act2 > 89. || act2 < 1. || act3 > 89. || act3 < 1.
                        || act4 > 89. || act4 < 1. || act5 > 89. || act5 < 1. || act6 > 89. || act6 < 1.)
                {
                    _controller.warning = true
                }
                else
                {
                    _controller.warning = false
                }

                stroke.clear()
                stroke.append("Ref", [act1, act2, act3, act4, act5, act6])
                stroke.append("Feedback", [0, 0, 0, 0, 0, 0])

            }
        }
    }
}
