#include "Actuator.h"

/*
*   Constructor
*/
Actuator::Actuator()
{
    zero_reading = 0;
    end_reading = ADC_RES;

    actuatorDir = STOP;
}

/*
*   Store pin numbers in member variables
*/
void Actuator::setPins(const uint8_t& IN1_pin,const uint8_t& IN2_pin,const uint8_t& PWM_pin,const uint8_t& POT_pin)
{
    this->IN1_pin = IN1_pin;
    this->IN2_pin = IN2_pin;
    this->PWM_pin = PWM_pin;
    this->POT_pin = POT_pin;
}

/*
*   Initialize the potentiometer calibration values
*/
void Actuator::setPotCalibration(const uint16_t& _zero_reading,const uint16_t& _end_reading)
{
    if (_end_reading > ADC_RES) return;

    this->zero_reading = _zero_reading;
    this->end_reading = _end_reading;
}

/*
*   Move the actuator with an output ranging from -1 to 1, converted to PWM value
*   and set H-bridge state for direction
*/
void Actuator::move(const float& output)
{
    int8_t sign = 0;
    if (output < 0.)
    {
        actuatorDir = RETRACT;
        sign = -1;
    }
    else if (output > 0.)
    {
        actuatorDir = EXTEND;
        sign = 1;
    }
    else actuatorDir = STOP;

    uint16_t pwm_out = (output * sign * (float)PWM_RES) + 0.5;
    
    switch (actuatorDir)
    {
        case RETRACT:
            digitalWrite(IN1_pin, HIGH);
            digitalWrite(IN2_pin, LOW);
            analogWrite(PWM_pin, pwm_out);
            break;
            
        case EXTEND:
            digitalWrite(IN1_pin, LOW);
            digitalWrite(IN2_pin, HIGH);
            analogWrite(PWM_pin, pwm_out);
            break;

        case STOP:
            digitalWrite(IN1_pin, HIGH);
            digitalWrite(IN2_pin, HIGH);
            analogWrite(PWM_pin, LOW);
            break;
          
        default:
            break;
    }
}

/*
*   Convert the read analog input to length in meters
*/
float Actuator::convIn(const uint16_t& input, const uint16_t& in_low, const uint16_t& in_high)
{
    return (float)(input - in_low) * posMax / (float)(in_high - in_low);
}

/*
*   Read the potentiometer input with an average of 10 readings
*/
float Actuator::readPosition()
{
    static const uint8_t TOT_READINGS = 10;
    
    float input = 0.0;

    for (uint8_t reading = 0; reading < TOT_READINGS; reading++)
    {
        input += (float)analogRead(POT_pin);
    }

    uint16_t avg_reading = (uint16_t) (input / (float)TOT_READINGS + 0.5);
    
    return convIn(avg_reading, zero_reading, end_reading);
}



