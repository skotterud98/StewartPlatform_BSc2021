#include "oscillator.h"

Oscillator::Oscillator(QObject *parent) : QObject(parent)
{
    gui_state = AMPLITUDE;
}

std::vector<std::vector<double>> Oscillator::sample_sine(const double& t_)
{
    std::vector<std::vector<double>> dof(2, std::vector<double>(6));

    dof[POS][0] = surge_A * sin(2.*PI * surge_freq * t_ + surge_offset) + surge_bias;
    dof[POS][1] = sway_A * sin(2.*PI * sway_freq * t_ + sway_offset) + sway_bias;
    dof[POS][2] = heave_A * sin(2.*PI * heave_freq * t_ + heave_offset) + heave_bias;

    dof[POS][3] = roll_A * (PI/180.) * sin(2.*PI * roll_freq * t_ + roll_offset) + roll_bias;
    dof[POS][4] = pitch_A * (PI/180.) * sin(2.*PI * pitch_freq * t_ + pitch_offset) + pitch_bias;
    dof[POS][5] = yaw_A * (PI/180.) * sin(2.*PI * yaw_freq * t_ + yaw_offset) + yaw_bias;


    dof[VEL][0] = surge_A * 2.*PI * surge_freq * cos(2*PI * surge_freq * t_ + surge_offset);
    dof[VEL][1] = sway_A * 2.*PI * sway_freq * cos(2*PI * sway_freq * t_ + sway_offset);
    dof[VEL][2] = heave_A * 2.*PI * heave_freq * cos(2*PI * heave_freq * t_ + heave_offset);

    dof[VEL][3] = roll_A * (PI/180.) * 2.*PI * roll_freq * cos(2*PI * roll_freq * t_ + roll_offset);
    dof[VEL][4] = pitch_A * (PI/180.) * 2.*PI * pitch_freq * cos(2*PI * pitch_freq * t_ + pitch_offset);
    dof[VEL][5] = yaw_A * (PI/180.) * 2.*PI * yaw_freq * cos(2*PI * yaw_freq * t_ + yaw_offset);

    return dof;
}

void Oscillator::set_amp()
{
    if (gui_state != AMPLITUDE)
    {
        gui_state = AMPLITUDE;
    }
}

void Oscillator::set_phase()
{
    if (gui_state != PHASE)
    {
        gui_state = PHASE;
    }
}

void Oscillator::set_freq()
{
    if (gui_state != FREQUENCY)
    {
        gui_state = FREQUENCY;
    }
}

void Oscillator::set_surge(const double& slider_value)
{
    switch (gui_state)
    {
    case AMPLITUDE:
        surge_A = slider_value * gain_A[0];
        emit surge_changed((uint8_t)(surge_A*1000));
        qDebug() << "Surge amplitude changed: " << surge_A;
        break;

    case PHASE:
        surge_offset = slider_value * gain_phase[0];
        emit surge_changed(surge_offset);
        qDebug() << "Surge offset changed: " << surge_offset;
        break;

    case FREQUENCY:
        surge_freq = slider_value * gain_freq[0];
        emit surge_changed(surge_freq);
        qDebug() << "Surge frequency changed: " << surge_freq;
        break;

    default:
        break;
    }

}

void Oscillator::set_sway(const double& slider_value)
{
    switch (gui_state)
    {
    case AMPLITUDE:
        sway_A = slider_value * gain_A[1];
        emit sway_changed(sway_A);
        qDebug() << "Sway amplitude changed: " << sway_A;
        break;
    case PHASE:
        sway_offset = slider_value * gain_phase[1];
        emit sway_changed(sway_offset);
        qDebug() << "Sway offset changed: " << sway_offset;
        break;
    case FREQUENCY:
        sway_freq = slider_value * gain_freq[1];
        emit sway_changed(sway_freq);
        qDebug() << "Sway frequency changed: " << sway_freq;
        break;
    default:
        break;
    }
}

void Oscillator::set_heave(const double& slider_value)
{
    switch (gui_state)
    {
    case AMPLITUDE:
        heave_A = slider_value * gain_A[2];
        emit heave_changed(surge_A);
        qDebug() << "Heave amplitude changed: " << heave_A;
        break;
    case PHASE:
        heave_offset = slider_value * gain_phase[2];
        emit heave_changed(heave_offset);
        qDebug() << "Heave offset changed: " << heave_offset;
        break;
    case FREQUENCY:
        heave_freq = slider_value * gain_freq[2];
        emit heave_changed(surge_freq);
        qDebug() << "Heave frequency changed: " << heave_freq;
        break;
    default:
        break;
    }
}

void Oscillator::set_roll(const double& slider_value)
{
    switch (gui_state)
    {
    case AMPLITUDE:
        roll_A = slider_value * gain_A[3];
        emit roll_changed(roll_A);
        qDebug() << "Roll amplitude changed: " << roll_A;
        break;
    case PHASE:
        roll_offset = slider_value * gain_phase[3];
        emit roll_changed(roll_offset);
        qDebug() << "Roll offset changed: " << roll_offset;
        break;
    case FREQUENCY:
        roll_freq = slider_value * gain_freq[3];
        emit roll_changed(roll_freq);
        qDebug() << "Roll frequency changed: " << roll_freq;
        break;
    default:
        break;
    }
}

void Oscillator::set_pitch(const double& slider_value)
{
    switch (gui_state)
    {
    case AMPLITUDE:
        pitch_A = slider_value * gain_A[4];
        emit pitch_changed(pitch_A);
        qDebug() << "Pitch amplitude changed: " << pitch_A;
        break;
    case PHASE:
        pitch_offset = slider_value * gain_phase[4];
        emit pitch_changed(pitch_offset);
        qDebug() << "Pitch offset changed: " << pitch_offset;
        break;
    case FREQUENCY:
        pitch_freq = slider_value * gain_freq[4];
        emit pitch_changed(pitch_freq);
        qDebug() << "Pitch frequency changed: " << pitch_freq;
        break;
    default:
        break;
    }
}

void Oscillator::set_yaw(const double& slider_value)
{
    switch (gui_state)
    {
    case AMPLITUDE:
        yaw_A = slider_value * gain_A[5];
        emit yaw_changed(yaw_A);
        qDebug() << "Yaw amplitude changed: " << yaw_A;
        break;
    case PHASE:
        yaw_offset = slider_value * gain_phase[5];
        emit yaw_changed(yaw_offset);
        qDebug() << "Yaw offset changed: " << yaw_offset;
        break;
    case FREQUENCY:
        yaw_freq = slider_value * gain_freq[5];
        emit yaw_changed(yaw_freq);
        qDebug() << "Yaw frequency changed: " << yaw_freq;
        break;
    default:
        break;
    }
}

double Oscillator::get_slider_surge()
{
    switch (gui_state)
    {
    case AMPLITUDE:
        return surge_A / gain_A[0];
        break;
    case PHASE:
        return surge_offset / gain_phase[0];
        break;
    case FREQUENCY:
        return surge_freq / gain_freq[0];
        break;
    default:
        return -1.;
    }
}

double Oscillator::get_slider_sway()
{
    switch (gui_state)
    {
    case AMPLITUDE:
        return sway_A / gain_A[1];
        break;
    case PHASE:
        return sway_offset / gain_phase[1];
        break;
    case FREQUENCY:
        return sway_freq / gain_freq[1];
        break;
    default:
        return -1.;
    }
}

double Oscillator::get_slider_heave()
{
    switch (gui_state)
    {
    case AMPLITUDE:
        return heave_A / gain_A[2];
        break;
    case PHASE:
        return heave_offset / gain_phase[2];
        break;
    case FREQUENCY:
        return heave_freq / gain_freq[2];
        break;
    default:
        return -1.;
    }
}

double Oscillator::get_slider_roll()
{
    switch (gui_state)
    {
    case AMPLITUDE:
        return roll_A / gain_A[3];
        break;
    case PHASE:
        return roll_offset / gain_phase[3];
        break;
    case FREQUENCY:
        return roll_freq / gain_freq[3];
        break;
    default:
        return -1.;
    }
}

double Oscillator::get_slider_pitch()
{
    switch (gui_state)
    {
    case AMPLITUDE:
        return pitch_A / gain_A[4];
        break;
    case PHASE:
        return pitch_offset / gain_phase[4];
        break;
    case FREQUENCY:
        return pitch_freq / gain_freq[4];
        break;
    default:
        return -1.;
    }
}

double Oscillator::get_slider_yaw()
{
    switch (gui_state)
    {
    case AMPLITUDE:
        return yaw_A / gain_A[5];
        break;
    case PHASE:
        return yaw_offset / gain_phase[5];
        break;
    case FREQUENCY:
        return yaw_freq / gain_freq[5];
        break;
    default:
        return -1.;
    }
}































