#include "src/Controller.h"
#include "src/CANbus.h"

#define SerialUSB Serial // Comment out if native port is used

/************************************** Shield pins *************************************/

// Motor driver H-bridge pins (direction)
const uint8_t M1_IN1 = 11;
const uint8_t M1_IN2 = 12;
const uint8_t M2_IN1 = 10;
const uint8_t M2_IN2 = 9;
const uint8_t M3_IN1 = 5;
const uint8_t M3_IN2 = 6;
const uint8_t M4_IN1 = 22;
const uint8_t M4_IN2 = 24;
const uint8_t M5_IN1 = 28;
const uint8_t M5_IN2 = 26;
const uint8_t M6_IN1 = 30;
const uint8_t M6_IN2 = 32;


// Motor driver PWM pins
const uint8_t M1_PWM = 13;
const uint8_t M2_PWM = 8;
const uint8_t M3_PWM = 7;
const uint8_t M4_PWM = 4;
const uint8_t M5_PWM = 3;
const uint8_t M6_PWM = 2;


// Analog inputs
const uint8_t AMP_SENSE = A0;

const uint8_t M1_POT = A1;
const uint8_t M2_POT = A2;
const uint8_t M3_POT = A3;
const uint8_t M4_POT = A4;
const uint8_t M5_POT = A5;
const uint8_t M6_POT = A6;


/************************************** Global variables & objects *************************************/

// Grouping the pins together in arrays with one column for each actuator/motor-driver
const uint8_t IN1_PINS[MOTORS_TOT]  = { M1_IN1, M2_IN1, M3_IN1, M4_IN1, M5_IN1, M6_IN1 };
const uint8_t IN2_PINS[MOTORS_TOT]  = { M1_IN2, M2_IN2, M3_IN2, M4_IN2, M5_IN2, M6_IN2 };
const uint8_t PWM_PINS[MOTORS_TOT]  = { M1_PWM, M2_PWM, M3_PWM, M4_PWM, M5_PWM, M6_PWM };
const uint8_t POT_PINS[MOTORS_TOT]  = { M1_POT, M2_POT, M3_POT, M4_POT, M5_POT, M6_POT };

// Arrays of gains to the controller
const float kp[MOTORS_TOT]     = { 245.65, 245.65, 245.65, 245.65, 245.65, 245.65 };    // Proportional gain
const float ki[MOTORS_TOT]     = { 0., 0., 0., 0., 0., 0. };    // Integral gain
const float kd[MOTORS_TOT]     = { 0., 0., 0., 0., 0., 0. };    // Derivative gain
const float kff[MOTORS_TOT]    = { 19.6, 19.6, 19.6, 19.6, 19.6, 19.6 };    // Feedforward gain 
const float N = 10; // Derivative filter coeffecient  

// Main controller object which includes the regulator alghorithm and six actuator objects.
// Actuator/motor-driver pins as parameters for constructor to initialize actuator objects
Controller control(IN1_PINS, IN2_PINS, PWM_PINS, POT_PINS);

// CAN-bus handler which deals with communication and keep track of what state the platform is in
CANbus can(&control);

// Sampling variables
const uint16_t SAMPLETIME = 10;  // [ms]
uint32_t currentTime = 0;
uint32_t lastTime = 0;

// Variables to keep track of CAN input error
uint8_t err_count = 0;
bool checkError = false;


/********************************************** Main ***************************************************/

/*
*   Init-function
*/
void setup()
{
    SerialUSB.begin(115200);

    analogReadResolution(12);   // Set ADC resolution to 12 bit
    analogWriteResolution(12);  // Set PWM resolution to 12 bit

    for (int num = 0; num < MOTORS_TOT; num++)
    {
        pinMode(IN1_PINS[num], OUTPUT);
        pinMode(IN2_PINS[num], OUTPUT);     // Config motor driver pins as ouputs
        pinMode(PWM_PINS[num], OUTPUT);
    }

    control.initTunings(SAMPLETIME, N, kp, ki, kd, kff);  // Configure the controller object with sampletime, gains and filter constant

    Can0.begin(500000);       // Init Can0 object with 500kbit/s baud
    Can0.attachObj(&can);     // Attach can object to Can0

    Can0.setRXFilter(SETPOINT_MB, 0xA0, 0x7FC, false);    // syntax: mailbox, id, mask, extended
    can.setCallback(SETPOINT_MB);   // Activate callback for incoming CAN messages
}


/*
*   Infinite loop-function
*/
void loop() 
{
    // Store current number of milliseconds since program startup
    currentTime = millis();

    if (currentTime - lastTime >= SAMPLETIME && can.received())
    {
        lastTime = currentTime;
        err_count = 0;

        // Deactivate callback for incoming CAN messages
        can.removeCallback(SETPOINT_MB);

        // Reads each actuators position (PV - process variable)
        control.read_PV();

        // Computes a new output and direction of each actuator, based on given setpoint
        // and sensor feedback. Includes a PID controller with velocity feedforward.
        control.calcNewOutput();

        // Move all actuators using this new calculated output
        control.actuate();

        // Replies to CAN-bus with feedback position and velocity data
        can.reply();

        // Reset the boolean check for incoming actuator messages
        can.reset();

        // Reactivate callback for for incoming CAN messages
        can.setCallback(SETPOINT_MB);

        // Set checkError variable to true, to start tracking sampling time of CAN input
        if(!checkError) { checkError = true; }

    }
    else if (currentTime - lastTime >= SAMPLETIME*1.2 && checkError) // Check if sampletime has passed with 20% margin
    {
        lastTime = currentTime;
        err_count++; // Count up error-counter
        can.reset();

        if (err_count > 3)  // if sampletime has passed with 20% margin over 3 times in a row
        {
            SerialUSB.println("ERROR");
            control.actuate(0);               // Stop all actuators
            control.reset_integrator();
            
            can.removeCallback(SETPOINT_MB);
            while(CANflush());                // Flush CAN rx buffer
            can.reset();
            can.setCallback(SETPOINT_MB);

            checkError = false;
            err_count = 0;
        }
    }
}

/*-------------------------------------------- End of Main ---------------------------------------------------*/



/*************************************** Global function definitions **********************************************/

bool CANflush()
{
    static CAN_FRAME rxFlush;

    if (Can0.rx_avail()) 
    {
        Can0.get_rx_buff(rxFlush);
        return true;
    }
    
    return false;
}
