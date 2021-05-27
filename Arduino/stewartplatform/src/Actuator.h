#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator
{
    public:

        enum Direction
        {   
            EXTEND, 
            RETRACT, 
            STOP 
        };

        Actuator();
        void setPins(const uint8_t& IN1_pin, const uint8_t& IN2_pin, const uint8_t& PWM_pin, const uint8_t& POT_pin);
        void setPotCalibration(const uint16_t& _zeroReading, const uint16_t& _endReading);

        void move(const float& output);         
        
        float readPosition();

    private:
        float convIn(const uint16_t& input, const uint16_t& in_low, const uint16_t& in_high);
    
        uint8_t IN1_pin;
        uint8_t IN2_pin;
        uint8_t PWM_pin;
        uint8_t POT_pin;

        Direction actuatorDir;

        uint16_t zero_reading;
        uint16_t end_reading;
    
        const uint16_t PWM_RES  = 4095;
        const uint16_t ADC_RES  = 4095;

        const float posMin      = 0.0;
        const float posMax      = 0.09;
        
        const float velMin      = -0.06;
        const float velMax      = 0.06;
};

#endif
