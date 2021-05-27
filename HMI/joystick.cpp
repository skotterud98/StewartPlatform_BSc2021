#include "joystick.h"

Joystick::Joystick(QObject *parent)
    : QObject(parent), neutralHeave(0.0485)
{
    m_joyX = 0.;
    m_joyY = 0.;

    m_roll = 0.;
    m_pitch = 0.;

    m_responseK = 0.5;
    m_maxAngle = 10.;

    m_dof <<   0., 0., neutralHeave, 0., 0., 0.,
                0., 0., 0., 0., 0., 0.;
}

double Joystick::getResponse() const
{
    return m_responseK;
}

void Joystick::setResponse(const double &newResponse)
{
    if (newResponse == m_responseK)
        return;
    m_responseK = newResponse;
    emit responseChanged(m_responseK);
}

double Joystick::getRange() const
{
    return m_maxAngle;
}

void Joystick::setRange(const double &newRange)
{
    if (newRange == m_maxAngle)
        return;
    m_maxAngle = newRange;
    emit rangeChanged(m_maxAngle);
}

double Joystick::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

void Joystick::reset()
{
    m_joyX = 0.;
    m_joyY = 0.;

    m_roll = 0.;
    m_pitch = 0.;

    m_responseK = 0.5;
    m_maxAngle = 10.;
}

Eigen::Matrix<double, 2, 6>& Joystick::sample()
{
    double new_K = 0.08 * m_responseK;
    double prev_K = 1. - new_K;

    double roll_in = -(round(m_joyY * 100.) / 100.) * m_maxAngle * PI / 180.;
    double pitch_in = (round(m_joyX * 100.) / 100.) * m_maxAngle * PI / 180.;

    m_roll = new_K * roll_in + prev_K * m_roll;
    m_pitch = new_K * pitch_in + prev_K * m_pitch;

    m_dof(POS, ROLL) = m_roll;
    m_dof(POS, PITCH) = m_pitch;

    return m_dof;
}











