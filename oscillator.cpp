#include "oscillator.h"

Oscillator::Oscillator(QObject *parent)
    : QObject(parent), m_heaveBias(0.0485)
{
    // Initial oscillator parameters for amptlitude, phase and frequency
    resetAmp();
    resetPhase();
    resetFreq();

    m_run = true;
    m_time = 0.;
}

void Oscillator::resetAmp()
{
    m_surge[Amp] = 0.;
    m_sway[Amp] = 0.;
    m_heave[Amp] = 0.;
    m_roll[Amp] = 0.;
    m_pitch[Amp] = 0.;
    m_yaw[Amp] = 0.;
}

void Oscillator::resetPhase()
{
    m_surge[Phase] = 0.;
    m_sway[Phase] = - PI / 2;
    m_heave[Phase] = 0.;
    m_roll[Phase] = 0.;
    m_pitch[Phase] = - PI / 2;
    m_yaw[Phase] = 0.;
}

void Oscillator::resetFreq()
{
    m_surge[Freq] = 0.2;
    m_sway[Freq] = 0.2;
    m_heave[Freq] = 0.2;
    m_roll[Freq] = 0.15;
    m_pitch[Freq] = 0.15;
    m_yaw[Freq] = 0.15;
}


// Set-Get function definitions

double Oscillator::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

/*
double Oscillator::getTime()
{
    return m_time;
}
*/
void Oscillator::reset()
{
    resetAmp();
    resetPhase();
    resetFreq();
    m_time = 0.;
    m_run = true;
}


/* ################################# Amplitude Sliders ##########################################*/

double Oscillator::getSurgeAmp() const { return m_surge[Amp] * 1000.; }

void Oscillator::setSurgeAmp(const double &sliderVal)
{
    if (sliderVal == m_surge[Amp] * 1000.)
        return;
    m_surge[Amp] = sliderVal / 1000.;
    emit surgeAmpChanged(m_surge[Amp]);
}

double Oscillator::getSwayAmp() const { return m_sway[Amp] * 1000.; }

void Oscillator::setSwayAmp(const double &sliderVal)
{
    if (sliderVal == m_sway[Amp] * 1000.)
        return;
    m_sway[Amp] = sliderVal / 1000.;
    emit swayAmpChanged(m_sway[Amp]);
}

double Oscillator::getHeaveAmp() const { return m_heave[Amp] * 1000.; }

void Oscillator::setHeaveAmp(const double &sliderVal)
{
    if (sliderVal == m_heave[Amp] * 1000.)
        return;
    m_heave[Amp] = sliderVal / 1000.;
    emit heaveAmpChanged(m_heave[Amp]);
}

double Oscillator::getRollAmp() const { return m_roll[Amp]; }

void Oscillator::setRollAmp(const double &sliderVal)
{
    if (sliderVal == m_roll[Amp])
        return;
    m_roll[Amp] = sliderVal;
    emit rollAmpChanged(m_roll[Amp]);
}

double Oscillator::getPitchAmp() const { return m_pitch[Amp]; }

void Oscillator::setPitchAmp(const double &sliderVal)
{
    if (sliderVal == m_pitch[Amp])
        return;
    m_pitch[Amp] = sliderVal;
    emit pitchAmpChanged(m_pitch[Amp]);
}

double Oscillator::getYawAmp() const { return m_yaw[Amp]; }

void Oscillator::setYawAmp(const double &sliderVal)
{
    if (sliderVal == m_yaw[Amp])
        return;
    m_yaw[Amp] = sliderVal;
    emit yawAmpChanged(m_yaw[Amp]);
}


/* ################################# Phase Sliders ##########################################*/

double Oscillator::getSurgePhase() const { return m_surge[Phase] / (2 * PI) + 0.5; }

void Oscillator::setSurgePhase(const double &sliderVal)
{
    if (sliderVal == m_surge[Phase] / (2 * PI) + 0.5 )
        return;
    m_surge[Phase] = (sliderVal - 0.5) * 2 * PI;
    emit surgePhaseChanged(m_surge[Phase]);
}

double Oscillator::getSwayPhase() const { return m_sway[Phase] / (2 * PI) + 0.5; }

void Oscillator::setSwayPhase(const double &sliderVal)
{
    if (sliderVal == m_sway[Phase] / (2 * PI) + 0.5)
        return;
    m_sway[Phase] = (sliderVal - 0.5) * 2 * PI;
    emit swayPhaseChanged(m_sway[Phase]);
}

double Oscillator::getHeavePhase() const { return m_heave[Phase] / (2 * PI) + 0.5; }

void Oscillator::setHeavePhase(const double &sliderVal)
{
    if (sliderVal == m_heave[Phase] / (2 * PI) + 0.5)
        return;
    m_heave[Phase] = (sliderVal - 0.5) * 2 * PI;
    emit heavePhaseChanged(m_heave[Phase]);
}

double Oscillator::getRollPhase() const { return m_roll[Phase] / (2 * PI) + 0.5; }

void Oscillator::setRollPhase(const double &sliderVal)
{
    if (sliderVal == m_roll[Phase] / (2 * PI) + 0.5)
        return;
    m_roll[Phase] = (sliderVal - 0.5) * 2 * PI;
    emit rollPhaseChanged(m_roll[Phase]);
}

double Oscillator::getPitchPhase() const { return m_pitch[Phase] / (2 * PI) + 0.5; }

void Oscillator::setPitchPhase(const double &sliderVal)
{
    if (sliderVal == m_pitch[Phase] / (2 * PI) + 0.5)
        return;
    m_pitch[Phase] = (sliderVal - 0.5) * 2 * PI;
    emit pitchPhaseChanged(m_pitch[Phase]);
}

double Oscillator::getYawPhase() const { return m_yaw[Phase] / (2 * PI) + 0.5; }

void Oscillator::setYawPhase(const double &sliderVal)
{
    if (sliderVal == m_yaw[Phase] / (2 * PI) + 0.5)
        return;
    m_yaw[Phase] = (sliderVal - 0.5) * 2 * PI;
    emit yawPhaseChanged(m_yaw[Phase]);
}


/* ################################# Frequency Sliders #######################################*/

double Oscillator::getSurgeFreq() const { return m_surge[Freq]; }

void Oscillator::setSurgeFreq(const double &sliderVal)
{
    if (sliderVal == m_surge[Freq])
        return;
    m_surge[Freq] = sliderVal;
    emit surgeFreqChanged(m_surge[Freq]);
}

double Oscillator::getSwayFreq() const { return m_sway[Freq]; }

void Oscillator::setSwayFreq(const double &sliderVal)
{
    if (sliderVal == m_sway[Freq])
        return;
    m_sway[Freq] = sliderVal;
    emit swayFreqChanged(m_sway[Freq]);
}

double Oscillator::getHeaveFreq() const { return m_heave[Freq]; }

void Oscillator::setHeaveFreq(const double &sliderVal)
{
    if (sliderVal == m_heave[Freq])
        return;
    m_heave[Freq] = sliderVal;
    emit heaveFreqChanged(m_heave[Freq]);
}

double Oscillator::getRollFreq() const { return m_roll[Freq]; }

void Oscillator::setRollFreq(const double &sliderVal)
{
    if (sliderVal == m_roll[Freq])
        return;
    m_roll[Freq] = sliderVal;
    emit rollFreqChanged(m_roll[Freq]);
}

double Oscillator::getPitchFreq() const { return m_pitch[Freq]; }

void Oscillator::setPitchFreq(const double &sliderVal)
{
    if (sliderVal == m_pitch[Freq])
        return;
    m_pitch[Freq] = sliderVal;
    emit pitchFreqChanged(m_pitch[Freq]);
}

double Oscillator::getYawFreq() const { return m_yaw[Freq]; }

void Oscillator::setYawFreq(const double &sliderVal)
{
    if (sliderVal == m_yaw[Freq])
        return;
    m_yaw[Freq] = sliderVal;
    emit yawFreqChanged(m_yaw[Freq]);
}


bool Oscillator::getRun() const { return m_run; }

void Oscillator::setRun(const bool &switchState)
{
    if(switchState == m_run)
        return;
    m_run = switchState;
    emit runChanged(m_run);
}


Eigen::Matrix<double, 2, 6>& Oscillator::sample()
{
    static double surgePrev[2]  = { 0., 0.};
    static double swayPrev[2]   = { 0., 0.};
    static double heavePrev[2]  = { 0., 0.};
    static double rollPrev[2]   = { 0., 0.};
    static double pitchPrev[2]  = { 0., 0.};
    static double yawPrev[2]    = { 0., 0.};


    static double surge[3]      = { 0., 0., m_surge[Freq]};
    static double sway[3]       = { 0., 0., m_sway[Freq]};
    static double heave[3]      = { 0., 0., m_heave[Freq]};
    static double roll[3]       = { 0., 0., m_roll[Freq]};
    static double pitch[3]      = { 0., 0., m_pitch[Freq]};
    static double yaw[3]        = { 0., 0., m_yaw[Freq]};

    static double new_K = 0.01;
    static double prev_K = 1 - new_K;


    if (surge[Amp] <= 0.0005 || (m_surge[Freq] != surge[Freq] && fmod(m_time, 1./surge[Freq]) <= 0.01 && fmod(m_time, 1./m_surge[Freq]) <= 0.01))
        surge[Freq] = m_surge[Freq];

    if (sway[Amp] <= 0.0005 || (m_sway[Freq] != sway[Freq] && fmod(m_time, 1./sway[Freq]) <= 0.01 && fmod(m_time, 1./m_sway[Freq]) <= 0.01))
        sway[Freq] = m_sway[Freq];

    if (heave[Amp] <= 0.0005 || (m_heave[Freq] != heave[Freq] && fmod(m_time, 1./heave[Freq]) <= 0.01 && fmod(m_time, 1./m_heave[Freq]) <= 0.01))
        heave[Freq] = m_heave[Freq];

    if (roll[Amp] <= 0.00001 || (m_roll[Freq] != roll[Freq] && fmod(m_time, 1./roll[Freq]) <= 0.01 && fmod(m_time, 1./m_roll[Freq]) <= 0.01))
        roll[Freq] = m_roll[Freq];

    if (pitch[Amp] <= 0.00001 || (m_pitch[Freq] != pitch[Freq] && fmod(m_time, 1./pitch[Freq]) <= 0.01 && fmod(m_time, 1./m_pitch[Freq]) <= 0.01))
        pitch[Freq] = m_pitch[Freq];

    if (yaw[Amp] <= 0.00001 || (m_yaw[Freq] != yaw[Freq] && fmod(m_time, 1./yaw[Freq]) <= 0.01 && fmod(m_time, 1./m_yaw[Freq]) <= 0.01))
        yaw[Freq] = m_yaw[Freq];

    // Low pass filter on amplitude changes
    surge[Amp] = new_K * m_surge[Amp] + prev_K * surgePrev[Amp];
    sway[Amp] = new_K * m_sway[Amp] + prev_K * swayPrev[Amp];
    heave[Amp] = new_K * m_heave[Amp] + prev_K * heavePrev[Amp];
    roll[Amp] = new_K * m_roll[Amp] + prev_K * rollPrev[Amp];
    pitch[Amp] = new_K * m_pitch[Amp] + prev_K * pitchPrev[Amp];
    yaw[Amp] = new_K * m_yaw[Amp] + prev_K * yawPrev[Amp];

    // Low pass filter on phase changes
    surge[Phase] = new_K * m_surge[Phase] + prev_K * surgePrev[Phase];
    sway[Phase] = new_K * m_sway[Phase] + prev_K * swayPrev[Phase];
    heave[Phase] = new_K * m_heave[Phase] + prev_K * heavePrev[Phase];
    roll[Phase] = new_K * m_roll[Phase] + prev_K * rollPrev[Phase];
    pitch[Phase] = new_K * m_pitch[Phase] + prev_K * pitchPrev[Phase];
    yaw[Phase] = new_K * m_yaw[Phase] + prev_K * yawPrev[Phase];


    // Calculate the six sine waves position ( standard sine formula A*sin(wt + ø)+bias )
    m_dof(POS, 0) = surge[Amp] * sin(2.*PI * surge[Freq] * m_time + surge[Phase]);
    m_dof(POS, 1) = sway[Amp] * sin(2.*PI * sway[Freq] * m_time + sway[Phase]);
    m_dof(POS, 2) = heave[Amp] * sin(2.*PI * heave[Freq] * m_time + heave[Phase]) + m_heaveBias;

    m_dof(POS, 3) = roll[Amp] * (PI/180.) * sin(2.*PI * roll[Freq] * m_time + roll[Phase]);
    m_dof(POS, 4) = pitch[Amp] * (PI/180.) * sin(2.*PI * pitch[Freq] * m_time + pitch[Phase]);
    m_dof(POS, 5) = yaw[Amp] * (PI/180.) * sin(2.*PI * yaw[Freq] * m_time + yaw[Phase]);

    // Calculate the six sine waves velocity (derivative of sine formula)
    m_dof(VEL, 0) = surge[Amp] * 2.*PI * surge[Freq] * cos(2*PI * surge[Freq] * m_time + surge[Phase]);
    m_dof(VEL, 1) = sway[Amp] * 2.*PI * sway[Freq] * cos(2*PI * sway[Freq] * m_time + sway[Phase]);
    m_dof(VEL, 2) = heave[Amp] * 2.*PI * heave[Freq] * cos(2*PI * heave[Freq] * m_time + heave[Phase]);

    m_dof(VEL, 3) = roll[Amp] * (PI/180.) * 2.*PI * roll[Freq] * cos(2*PI * roll[Freq] * m_time + roll[Phase]);
    m_dof(VEL, 4) = pitch[Amp] * (PI/180.) * 2.*PI * pitch[Freq] * cos(2*PI * pitch[Freq] * m_time + pitch[Phase]);
    m_dof(VEL, 5) = yaw[Amp] * (PI/180.) * 2.*PI * yaw[Freq] * cos(2*PI * yaw[Freq] * m_time + yaw[Phase]);

    // Store amp and phase low pass filter prev-values for next iteration
    for (uint8_t i = 0; i < 2; i++)
    {
        surgePrev[i] = surge[i];
        swayPrev[i] = sway[i];
        heavePrev[i] = heave[i];
        rollPrev[i] = roll[i];
        pitchPrev[i] = pitch[i];
        yawPrev[i] = yaw[i];
    }

    if (m_run && !m_zeroAmpIn())
        m_time+= 0.01;

    return m_dof;
}


bool Oscillator::m_zeroAmpIn()
{
    return m_surge[Amp] == 0. && m_sway[Amp] == 0. && m_heave[Amp] == 0.
            && m_roll[Amp] == 0 && m_pitch[Amp] == 0. && m_yaw[Amp] == 0.;
}

























