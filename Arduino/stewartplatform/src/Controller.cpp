#include "Controller.h"

/*
*   Constructor. Set pins and calibrations for the six Actuator objects
*/
Controller::Controller(const uint8_t IN1_pin[], const uint8_t IN2_pin[], const uint8_t PWM_pin[], const uint8_t POT_pin[])
{
    for (uint8_t num = 0; num < MOTORS_TOT; num++)
    {
        act[num].setPins(IN1_pin[num], IN2_pin[num], PWM_pin[num], POT_pin[num]);
        act[num].setPotCalibration(potZero[num], potEnd[num]);

        i_sum[num]      = 0;
        prevError[num]  = 0;
        output[num]     = 0;
        
        kp[num]         = 0;
        ki[num]         = 0;
        kd[num]         = 0;
        kff[num]        = 0;
    }
    a = 0;
}

/*
*   Initalize the controller variables. Sample time, gains and filter coefficient for the pseudo-derivative
*/
void Controller::initTunings(const uint8_t& sampletime, const float& N, const float kp[], const float ki[], const float kd[], const float kff[])
{
    if (sampletime > 0)
    {
        for (uint8_t num = 0; num < MOTORS_TOT; num++)
        {
            if (kp[num] < 0 || ki[num] < 0 || kd[num] < 0 || kff[num] < 0) return;
        }

        this->sampletime_sec = ((float)sampletime) / 1000.0;
        
        for (uint8_t num = 0; num < MOTORS_TOT; num++)
        {
            this->kp[num]   = kp[num];
            this->ki[num]   = ki[num] * sampletime_sec;
            this->kd[num]   = kd[num] / sampletime_sec;
            this->kff[num]  = kff[num];
        }
        
        a = sampletime_sec / ( (1/N) + sampletime_sec);
    }
}

/*
*   Reads the each actuator position and store in member variable
*/
void Controller::read_PV()
{
    for (uint8_t num = 0; num < MOTORS_TOT; num ++)
    {
        this->sensorInput[num] = act[num].readPosition();
    }
}

/*
*   The control-loop. Including a PID controller for position and feedforward velocity
*/
void Controller::calcNewOutput()
{
    for (uint8_t num = 0; num < MOTORS_TOT; num++)
    {
        if (ref_pos[num] < 0.005)
        {
            ref_pos[num] = 0.005;
            ref_vel[num] = 0.;
        }
        if (ref_pos[num] > 0.0895)
        {
            ref_pos[num] = 0.0895;
            ref_vel[num] = 0.;
        }
        
        float input = sensorInput[num];
        float error = ref_pos[num] - input;
        float error_filt = (1. - a) * prevError[num] + a * error;
        float deltaError = error_filt - prevError[num];
        
        output[num] = kp[num] * error;
        
        i_sum[num] += ki[num] * error;
        if (i_sum[num] > 1.0) i_sum[num] = 1.0;
        else if (i_sum[num] < -1.0) i_sum[num] = -1.0;

        output[num] += i_sum[num] + kd[num] * deltaError;

        if (output[num] > 1.0) { output[num] = 1.0; }
        else if (output[num] < -1.0) { output[num] = -1.0; }

        output[num] += (kff[num] * ref_vel[num]);
        
        if (output[num] > 1.0) output[num] = 1.0;
        else if (output[num] < -1.0) output[num] = -1.0;

        prevError[num] = error_filt;
    }
}

/*
*   Sets accumulated integral term to zero
*/
void Controller::reset_integrator()
{
    for (uint8_t num = 0; num < MOTORS_TOT; num++)
    {
        i_sum[num] = 0;
    }
}

/*
*   Move actuator with the stored output.
*/
void Controller::actuate()
{
    for (uint8_t num = 0; num < MOTORS_TOT; num++)
    {
        act[num].move(this->output[num]);
    }
}

/*
*   Overloading to be able to enter a certain output in open-loop without going through the regulator.
*   This function with manual output also initialize the PID variables to current state.
*/
void Controller::actuate(const float& output)
{
    for (uint8_t num = 0; num < MOTORS_TOT; num++)
    {
        act[num].move(output);
    }
}


void Controller::set_ref_vel(const float ref_vel[])
{
    for (uint8_t num = 0; num < 6; num++)
    {
        this->ref_vel[num] = ref_vel[num];
    }
}

void Controller::set_ref_pos(const float ref_pos[])
{
    for (uint8_t num = 0; num < 6; num++)
    {
        this->ref_pos[num] = ref_pos[num];
    }
}


float Controller::get_sensorInput(const uint8_t& actuatorNum) { return this->sensorInput[actuatorNum]; }

float Controller::get_prevError(const uint8_t& actuatorNum) { return this->prevError[actuatorNum]; }

float Controller::get_sampletime_sec() { return this->sampletime_sec; }

/*
*   Reads the current-consumption from the Hall sensor on the shield
*/
uint8_t Controller::getAmpere()
{
    uint16_t reading = analogRead(A0);
    
    if (reading < 2047) reading = 2047;
    
    return (uint8_t) map(reading, 2047, 4095, 0, 255);
}
