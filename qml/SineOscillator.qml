import QtQml.Models 2.2
import QtQml 2.15
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4
import "Components" as Components

Page {
    width: 800
    height: 430
    title: "Sine Oscillator"

    Components.BackgroundPage {
        id: root
        anchors.fill: parent
        state: "ampState" // inital state

        property double ampFrom: 0.
        property var ampTo: [40., 40., 35., 20., 20., 35.]
        property var ampUnit: ["mm", "mm", "mm", "deg", "deg", "deg"]
        property double ampStep: 1.

        property double phaseFrom: 0.
        property double phaseTo: 1.
        property string phaseUnit: "rad"
        property double phaseStep: 0.125

        property double freqFrom: 0.1
        property var freqTo: [0.4, 0.4, 0.25, 0.3, 0.3, 0.3]
        property string freqUnit: "Hz"
        property double freqStep: 0.05

        StatusIndicator {
            id: statusInd
            x: 650
            y: 370
            active: true
            color: _controller.runningProgram == "Sine Oscillator" ? "green" : "red"
        }

        Text {
            id: statusIndText
            x: 700
            y: 380
            text: qsTr("Active")
            color: "#db6221"
            font.bold: true
        }

        // Amplitude sliders
        Rectangle {
            id: ampSliders
            color: "transparent"
            visible: true

            Components.MySlider {
                id: surgeSliderAmp; sliderName: qsTr("SURGE"); x: root.width - 700; y: root.height - 265; sliderUnit: root.ampUnit[0]; from: root.ampFrom
                to: root.ampTo[0]; stepSize: root.ampStep; value: _oscillator.surgeAmp

                onMoved: _oscillator.surgeAmp = surgeSliderAmp.value
            }
            Components.MySlider {
                id: swaySliderAmp; sliderName: qsTr("SWAY"); x: root.width - 600; y: root.height - 265; sliderUnit: root.ampUnit[1]; from: root.ampFrom
                to: root.ampTo[1]; stepSize: root.ampStep; value: _oscillator.swayAmp

                onMoved: _oscillator.swayAmp = swaySliderAmp.value
            }
            Components.MySlider {
                id: heaveSliderAmp; sliderName: qsTr("HEAVE"); x: root.width - 500; y: root.height - 265; sliderUnit: root.ampUnit[2]; from: root.ampFrom
                to: root.ampTo[2]; stepSize: root.ampStep; value: _oscillator.heaveAmp

                onMoved: _oscillator.heaveAmp = heaveSliderAmp.value
            }
            Components.MySlider {
                id: rollSliderAmp; sliderName: qsTr("ROLL"); x: root.width - 400; y: root.height - 265; sliderUnit: root.ampUnit[3]; from: root.ampFrom
                to: root.ampTo[3]; stepSize: root.ampStep; value: _oscillator.rollAmp

                onMoved: _oscillator.rollAmp = rollSliderAmp.value
            }
            Components.MySlider {
                id: pitchSliderAmp; sliderName: qsTr("PITCH"); x: root.width - 300; y: root.height - 265; sliderUnit: root.ampUnit[4]; from: root.ampFrom
                to: root.ampTo[4]; stepSize: root.ampStep; value: _oscillator.pitchAmp

                onMoved: _oscillator.pitchAmp = pitchSliderAmp.value
            }
            Components.MySlider {
                id: yawSliderAmp; sliderName: qsTr("YAW"); x: root.width - 200; y: root.height - 265; sliderUnit: root.ampUnit[5]; from: root.ampFrom
                to: root.ampTo[5]; stepSize: root.ampStep; value: _oscillator.yawAmp

                onMoved: _oscillator.yawAmp = yawSliderAmp.value
            }
        }


        // Phase sliders
        Rectangle {
            id: phaseSliders
            color: "transparent"
            visible: false

            Components.MySlider {
                id: surgeSliderPhase; sliderName: qsTr("SURGE"); x: root.width - 700; y: root.height - 265; sliderUnit: root.phaseUnit; from: root.phaseFrom
                to: root.phaseTo; stepSize: root.phaseStep; phase: true; value: _oscillator.surgePhase

                onMoved: _oscillator.surgePhase = surgeSliderPhase.value
            }
            Components.MySlider {
                id: swaySliderPhase; sliderName: qsTr("SWAY"); x: root.width - 600; y: root.height - 265; sliderUnit: root.phaseUnit; from: root.phaseFrom
                to: root.phaseTo; stepSize: root.phaseStep; phase: true; value: _oscillator.swayPhase

                onMoved: _oscillator.swayPhase = swaySliderPhase.value
            }
            Components.MySlider {
                id: heaveSliderPhase; sliderName: qsTr("HEAVE"); x: root.width - 500; y: root.height - 265; sliderUnit: root.phaseUnit; from: root.phaseFrom
                to: root.phaseTo; stepSize: root.phaseStep; phase: true; value: _oscillator.heavePhase

                onMoved: _oscillator.heavePhase = heaveSliderPhase.value
            }
            Components.MySlider {
                id: rollSliderPhase; sliderName: qsTr("ROLL"); x: root.width - 400; y: root.height - 265; sliderUnit: root.phaseUnit; from: root.phaseFrom
                to: root.phaseTo; stepSize: root.phaseStep; phase: true; value: _oscillator.rollPhase

                onMoved: _oscillator.rollPhase = rollSliderPhase.value
            }
            Components.MySlider {
                id: pitchSliderPhase; sliderName: qsTr("PITCH"); x: root.width - 300; y: root.height - 265; sliderUnit: root.phaseUnit; from: root.phaseFrom
                to: root.phaseTo; stepSize: root.phaseStep; phase: true; value: _oscillator.pitchPhase

                onMoved: _oscillator.pitchPhase = pitchSliderPhase.value
            }
            Components.MySlider {
                id: yawSliderPhase; sliderName: qsTr("YAW"); x: root.width - 200; y: root.height - 265; sliderUnit: root.phaseUnit; from: root.phaseFrom
                to: root.phaseTo; stepSize: root.phaseStep; phase: true; value: _oscillator.yawPhase

                onMoved: _oscillator.yawPhase = yawSliderPhase.value
            }
        }


        // Frequency sliders
        Rectangle {
            id: freqSliders
            color: "transparent"
            visible: false

            Components.MySlider {
                id: surgeSliderFreq; sliderName: qsTr("SURGE"); x: root.width - 700; y: root.height - 265; sliderUnit: root.freqUnit; from: root.freqFrom
                to: root.freqTo[0]; stepSize: root.freqStep; value: _oscillator.surgeFreq

                onMoved: _oscillator.surgeFreq = surgeSliderFreq.value
            }
            Components.MySlider {
                id: swaySliderFreq; sliderName: qsTr("SWAY"); x: root.width - 600; y: root.height - 265; sliderUnit: root.freqUnit; from: root.freqFrom
                to: root.freqTo[1]; stepSize: root.freqStep; value: _oscillator.swayFreq

                onMoved: _oscillator.swayFreq = swaySliderFreq.value
            }
            Components.MySlider {
                id: heaveSliderFreq; sliderName: qsTr("HEAVE"); x: root.width - 500; y: root.height - 265; sliderUnit: root.freqUnit; from: root.freqFrom
                to: root.freqTo[2]; stepSize: root.freqStep; value: _oscillator.heaveFreq

                onMoved: _oscillator.heaveFreq = heaveSliderFreq.value
            }
            Components.MySlider {
                id: rollSliderFreq; sliderName: qsTr("ROLL"); x: root.width - 400; y: root.height - 265; sliderUnit: root.freqUnit; from: root.freqFrom
                to: root.freqTo[3]; stepSize: root.freqStep; value: _oscillator.rollFreq

                onMoved: _oscillator.rollFreq = rollSliderFreq.value
            }
            Components.MySlider {
                id: pitchSliderFreq; sliderName: qsTr("PITCH"); x: root.width - 300; y: root.height - 265; sliderUnit: root.freqUnit; from: root.freqFrom
                to: root.freqTo[4]; stepSize: root.freqStep; value: _oscillator.pitchFreq

                onMoved: _oscillator.pitchFreq = pitchSliderFreq.value
            }
            Components.MySlider {
                id: yawSliderFreq; sliderName: qsTr("YAW"); x: root.width - 200; y: root.height - 265; sliderUnit: root.freqUnit; from: root.freqFrom
                to: root.freqTo[5]; stepSize: root.freqStep; value: _oscillator.yawFreq

                onMoved: _oscillator.yawFreq = yawSliderFreq.value
            }
        }

        // Tab buttons for choosing which of the sliders is visible
        Components.MyTabButton {
            id: ampButton
            x: 45
            y: 66
            text: qsTr("Amplitude")
            onClicked: root.state = "ampState"
            checked: true
        }
        Components.MyTabButton {
            id: phaseButton
            x: 45
            y: 120
            text: qsTr("Phase")
            onClicked: root.state = "phaseState"
        }
        Components.MyTabButton {
            id: freqButton
            x: 45
            y: 174
            text: qsTr("Frequency")
            onClicked: root.state = "freqState"
        }

        // Reset amplitude button
        Components.MyButton {
            id: resetAmp
            x: 45
            y: 228
            text: qsTr("Reset")
            onClicked: {
                _oscillator.resetAmp()

                surgeSliderAmp.value = _oscillator.surgeAmp
                swaySliderAmp.value = _oscillator.swayAmp
                heaveSliderAmp.value = _oscillator.heaveAmp
                rollSliderAmp.value = _oscillator.rollAmp
                pitchSliderAmp.value = _oscillator.pitchAmp
                yawSliderAmp.value = _oscillator.yawAmp
            }
        }

        // Reset phase button
        Components.MyButton {
            id: resetPhase
            x: 45
            y: 228
            text: qsTr("Reset")
            onClicked: {
                _oscillator.resetPhase()

                surgeSliderPhase.value = _oscillator.surgePhase
                swaySliderPhase.value = _oscillator.swayPhase
                heaveSliderPhase.value = _oscillator.heavePhase
                rollSliderPhase.value = _oscillator.rollPhase
                pitchSliderPhase.value = _oscillator.pitchPhase
                yawSliderPhase.value = _oscillator.yawPhase
            }
        }

        // Reset frequency button
        Components.MyButton {
            id: resetFreq
            x: 45
            y: 228
            text: qsTr("Reset")
            onClicked: {
                _oscillator.resetAmp()
                surgeSliderAmp.value = _oscillator.surgeAmp
                swaySliderAmp.value = _oscillator.swayAmp
                heaveSliderAmp.value = _oscillator.heaveAmp
                rollSliderAmp.value = _oscillator.rollAmp
                pitchSliderAmp.value = _oscillator.pitchAmp
                yawSliderAmp.value = _oscillator.yawAmp

                _oscillator.resetFreq()
                surgeSliderFreq.value = _oscillator.surgeFreq
                swaySliderFreq.value = _oscillator.swayFreq
                heaveSliderFreq.value = _oscillator.heaveFreq
                rollSliderFreq.value = _oscillator.rollFreq
                pitchSliderFreq.value = _oscillator.pitchFreq
                yawSliderFreq.value = _oscillator.yawFreq
            }
        }

        // Run switch
        Components.MySwitch {
            id: runSw
            x: 45
            y: 300
            text: qsTr("Run")
            checked: _oscillator.run

            onClicked: {
                _oscillator.run = runSw.checked ? true : false
            }
        }


        Text {
            id: warningMsg
            x: 45
            text: "WARNING:  Stroke-length out of range"
            color: "#ff0000"
            font.bold: true
            visible: _controller.warning ? true : false
        }


        states: [
            State {
                name: "ampState"
                PropertyChanges { target: ampSliders; visible: true }
                PropertyChanges { target: phaseSliders; visible: false }
                PropertyChanges { target: freqSliders; visible: false }
                PropertyChanges { target: resetAmp; visible: true }
                PropertyChanges { target: resetPhase; visible: false }
                PropertyChanges { target: resetFreq; visible: false }
            },
            State {
                name: "phaseState"
                PropertyChanges { target: ampSliders; visible: false }
                PropertyChanges { target: phaseSliders; visible: true }
                PropertyChanges { target: freqSliders; visible: false }
                PropertyChanges { target: resetAmp; visible: false }
                PropertyChanges { target: resetPhase; visible: true }
                PropertyChanges { target: resetFreq; visible: false }
            },
            State {
                name: "freqState"
                PropertyChanges { target: ampSliders; visible: false }
                PropertyChanges { target: phaseSliders; visible: false }
                PropertyChanges { target: freqSliders; visible: true }
                PropertyChanges { target: resetAmp; visible: false }
                PropertyChanges { target: resetPhase; visible: false }
                PropertyChanges { target: resetFreq; visible: true }
            }
        ]
    }
}
















