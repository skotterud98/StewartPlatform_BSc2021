#include "CANbus.h"


/*
*   Constructor
*/
CANbus::CANbus(Controller* control_ptr)
{
    this->reset();

    msg_count = 0;

    this->control_ptr = control_ptr;
}

/*
*   CAN-bus receive ISR
*/
void CANbus::ref_ISR(CAN_FRAME* frame)
{
    static float ref_pos[MOTORS_TOT] = {0., 0., 0., 0., 0., 0.};
    static float ref_vel[MOTORS_TOT] = {0., 0., 0., 0., 0., 0.};
    static uint8_t j = 0;
    static uint8_t vel_dir = 0;

    switch (frame->id)
    {
        case 0xA0:      // Actuator 1-3 position ref

            j = 0;

            for (uint8_t i = 0; i < 3; i++)
            {
                uint16_t in_len = frame->data.byte[j] << 8;
                in_len += frame->data.byte[j + 1];
                
                ref_pos[i] = (float) in_len / 100000.;
                
                j+=2;
            }

            pos_msg[0] = true;
            break;

        case 0xA1:      // Actuator 4-6 position ref
            
            j = 0;

            for (uint8_t i = 3; i < 6; i++)
            {
                uint16_t in_len = frame->data.byte[j] << 8;
                in_len += frame->data.byte[j + 1];
                
                ref_pos[i] = (float) in_len / 100000.;

                j+=2;
                
                
            }

            pos_msg[1] = true;
            break;

        case 0xA2:    // Actuator 1-3 velocity ref and the direction (out/in) of the velocity
            
            j = 0;

            vel_dir = frame->data.byte[6];

            for (uint8_t i = 0; i < 3; i++)
            {
                uint16_t in_vel = frame->data.byte[j] << 8;
                in_vel += frame->data.byte[j + 1];

                ref_vel[i] = (float) in_vel / 1000000.;

                if (!((vel_dir >> i) & 1U))
                {
                    ref_vel[i] *= -1.;
                }

                j+=2;
            }

            vel_msg[0] = true;
            break;

        case 0xA3:    // Actuator 4-6 velocity ref and the direction (out/in) of the velocity
            
            j = 0;

            vel_dir = frame->data.byte[6];

            for (uint8_t i = 3; i < 6; i++)
            {
                uint16_t in_vel = frame->data.byte[j] << 8;
                in_vel += frame->data.byte[j + 1];
                
                ref_vel[i] = (float) in_vel / 1000000.;

                if(!((vel_dir >> (i-3)) & 1U))
                {
                    ref_vel[i] *= -1.;
                }

                j+=2;
            }

            vel_msg[1] = true;
            break;

        default:
            break;
    }


    if (pos_msg[0] && pos_msg[1] && vel_msg[0] && vel_msg[1])
    {
        control_ptr->set_ref_pos(ref_pos);
        control_ptr->set_ref_vel(ref_vel);
    }
}


/*
*   Frame interrupt handler. An inherited virtual function from the due_can library.
*   This fuction chooses what callback function to run based on the triggered mailbox.
*/
void CANbus::gotFrame(CAN_FRAME* frame, int mailbox)
{
    if(mailbox == SETPOINT_MB) this->ref_ISR(frame);
}

/*
*   Reply to CAN-bus with positions of the six actuators and the 12V current-consumption
*/
void CANbus::reply()
{
    static uint16_t out_pos[6];
    static uint8_t ampere = 0;

    for (uint8_t num = 0; num < MOTORS_TOT; num ++)
    {
        out_pos[num] = (uint16_t)(control_ptr->get_sensorInput(num) * 100000. + 0.5);
    }
    
    ampere = control_ptr->getAmpere();

    txFrame.id = 0xF0;
    txFrame.length = 6;

    txFrame.data.byte[0] = (uint8_t)(out_pos[0] >> 8);
    txFrame.data.byte[1] = (uint8_t) out_pos[0];
    txFrame.data.byte[2] = (uint8_t)(out_pos[1] >> 8);
    txFrame.data.byte[3] = (uint8_t) out_pos[1];
    txFrame.data.byte[4] = (uint8_t)(out_pos[2] >> 8);
    txFrame.data.byte[5] = (uint8_t) out_pos[2];
    
    Can0.sendFrame(txFrame);


    txFrame.id = 0xF1;
    txFrame.length = 7;

    txFrame.data.byte[0] = (uint8_t)(out_pos[3] >> 8);
    txFrame.data.byte[1] = (uint8_t) out_pos[3];
    txFrame.data.byte[2] = (uint8_t)(out_pos[4] >> 8);
    txFrame.data.byte[3] = (uint8_t) out_pos[4];
    txFrame.data.byte[4] = (uint8_t)(out_pos[5] >> 8);
    txFrame.data.byte[5] = (uint8_t) out_pos[5];
    txFrame.data.byte[6] = ampere;

    Can0.sendFrame(txFrame);
}

/*
*   Resets the boolean variables for each received message
*/
void CANbus::reset()
{
    pos_msg[0]  = false;
    pos_msg[1]  = false;
    vel_msg[0]  = false;
    vel_msg[1]  = false;
}

/*
*   Returns true if all 4 actuator reference messages is received
*/
bool CANbus::received() { return pos_msg[0] && pos_msg[1] && vel_msg[0] && vel_msg[1]; }


