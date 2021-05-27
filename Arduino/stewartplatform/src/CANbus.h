#ifndef CANBUS_H
#define CANBUS_H

#include <Arduino.h>
#include <due_can.h>
#include <variant.h>

#include "Controller.h"

enum CAN_Mailbox 
{
    SETPOINT_MB  = 0,
};

class CANbus: public CANListener
{
    public:
        CANbus(Controller* control_ptr);
        
        void reply();
        void reset();
        bool received();

    private:
        void gotFrame(CAN_FRAME* frame, int mailbox) override;
        void ref_ISR(CAN_FRAME* frame);

        volatile uint8_t msg_count;
        bool pos_msg[2];
        bool vel_msg[2];

        CAN_FRAME txFrame;
        Controller* control_ptr;
};


#endif
