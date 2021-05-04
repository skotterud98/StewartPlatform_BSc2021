import QtQuick 2.0
import QtQuick.Controls 2.0
import QtCharts 2.3
import "Components" as MyComponents



Page {
    width: 800
    height: 430
    title: "Setpoint Plot"
    MyComponents.BackgroundPage {
        anchors.fill: parent


        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -130
            height: 230
            width: 800
            color: "transparent"

            ChartView {
                id: transChart
                anchors.fill: parent
                legend.alignment: Qt.AlignRight
                animationOptions: ChartView.NoAnimation
                antialiasing: true
                backgroundColor: "#1a1a1a"

                property double heaveBias: 48.5

            }
        }


        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 50
            height: 230
            width: 800
            color: "transparent"

            ChartView {
                id: rotChart
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

            property real time_: 0.0

            onTriggered: {

                time_ += 0.1
                var surge = transChart.series("Surge")
                var sway = transChart.series("Sway")
                var heave = transChart.series("Heave")
                var roll = rotChart.series("Roll")
                var pitch = rotChart.series("Pitch")
                var yaw = rotChart.series("Yaw")


                if (!surge) {
                    surge = transChart.createSeries(ChartView.SeriesTypeLine, "Surge")

                    transChart.axisY().min = - 45
                    transChart.axisY().max = 45
                    transChart.axisY().tickCount = 5
                    transChart.axisY().titleText = "mm"
                    transChart.axisY().gridVisible = false
                    transChart.axisY().labelFormat = "%.0f"

                    transChart.axisX().labelFormat = "%.0f"
                    transChart.axisX().gridVisible = false
                    transChart.axisX().labelsVisible = false
                }
                if (!sway) {
                    sway = transChart.createSeries(ChartView.SeriesTypeLine, "Sway")
                }
                if (!heave) {
                    heave = transChart.createSeries(ChartView.SeriesTypeLine, "Heave")
                }


                if (!roll) {
                    roll = rotChart.createSeries(ChartView.SeriesTypeLine, "Roll")
                    roll.color = "violet"

                    rotChart.axisY().min = -40
                    rotChart.axisY().max = 40
                    rotChart.axisY().tickCount = 5
                    rotChart.axisY().titleText = "deg"
                    rotChart.axisY().gridVisible = false
                    rotChart.axisY().labelFormat = "%.0f"

                    rotChart.axisX().labelFormat = "%.0f"
                    rotChart.axisX().labelsVisible = true
                    rotChart.axisX().gridVisible = false
                }
                if (!pitch) {
                    pitch = rotChart.createSeries(ChartView.SeriesTypeLine, "Pitch")
                    pitch.color = "orangered"
                }

                if (!yaw) {
                    yaw = rotChart.createSeries(ChartView.SeriesTypeLine, "Yaw")
                    yaw.color = "mediumaquamarine"
                }

                surge.append(Math.round(time_ * 10) / 10, Math.round(_controller.surgeOut * 10) / 10)
                sway.append(Math.round(time_ * 10) / 10, Math.round(_controller.swayOut * 10) / 10)
                heave.append(Math.round(time_ * 10) / 10, Math.round((_controller.heaveOut - transChart.heaveBias) * 10) / 10)
                roll.append(Math.round(time_ * 10) / 10, Math.round(_controller.rollOut * 10) / 10)
                pitch.append(Math.round(time_ * 10) / 10, Math.round(_controller.pitchOut * 10) / 10)
                yaw.append(Math.round(time_ * 10) / 10, Math.round(_controller.yawOut * 10) / 10)


                if (Math.round(time_ * 10) / 10 > 5) {
                    transChart.axisX().max = Number(Math.round(time_ * 10) / 10)
                    transChart.axisX().min = transChart.axisX().max - 5;

                    rotChart.axisX().max = Number(Math.round(time_ * 10) / 10)
                    rotChart.axisX().min = rotChart.axisX().max - 5;
                } else {
                    transChart.axisX().max = 5;
                    transChart.axisX().min = 0;

                    rotChart.axisX().max = 5;
                    rotChart.axisX().min = 0;
                }
                transChart.axisX().tickCount = transChart.axisX().max - transChart.axisX().min + 1;
                rotChart.axisX().tickCount = rotChart.axisX().max - rotChart.axisX().min + 1;
            }
        }
    }
}
