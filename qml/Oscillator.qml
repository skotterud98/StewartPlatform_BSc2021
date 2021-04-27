import QtQuick 2.0

OscillatorForm
{
    freqButton.onClicked: {
        oscillator_.set_freq()
        surgeSlider.stepSize = 0.1
    }
    phaseButton.onClicked: {
        oscillator_.set_phase()
    }
    ampButton.onClicked: {
        oscillator_.set_amp()
    }

    //Slider signals to Cpp back-end
    surgeSlider.onValueChanged: {
        oscillator_.set_surge(surgeSlider.value)
    }
    swaySlider.onValueChanged: {
        oscillator_.set_sway(swaySlider.value)
    }
    heaveSlider.onValueChanged: {
        oscillator_.set_heave((heaveSlider.value))
    }
    rollSlider.onValueChanged: {
        oscillator_.set_roll(rollSlider.value)
    }
    pitchSlider.onValueChanged: {
        oscillator_.set_pitch(pitchSlider.value)
    }
    yawSlider.onValueChanged: {
        oscillator_.set_yaw(yawSlider.value)
    }

    Connections {
        target: oscillator_
        onSurge_changed: surgeTxt.text = param_value
        onSway_changed: swayTxt.text = param_value
        onHeave_changed: heaveTxt.text = param_value
        onRoll_changed: rollTxt.text = param_value
        onPitch_changed: pitchTxt.text = param_value
        onYaw_changed: yawTxt.text = param_value
    }
}
