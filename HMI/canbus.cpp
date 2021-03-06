#include "canbus.h"

CANbus::CANbus()
{
    if ((this->socket_ = socket(PF_CAN, SOCK_RAW | SOCK_NONBLOCK, CAN_RAW)) < 0)
    {
        perror("Socket");
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(this->socket_, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(this->socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind");
    }


    tx_len1.can_id = 0xA0;
    tx_len1.can_dlc = 6;

    tx_len2.can_id = 0xA1;
    tx_len2.can_dlc = 6;

    tx_vel1.can_id = 0xA2;
    tx_vel1.can_dlc = 7;

    tx_vel2.can_id = 0xA3;
    tx_vel2.can_dlc = 7;
}

CANbus::~CANbus()
{
    if (close(this->socket_) < 0)
    {
        perror("Close");
    }
}

void CANbus::send_data(const double stroke_len[], const double stroke_vel[])
{
    static uint16_t out_len[6];
    static uint16_t out_vel[6];

    uint16_t sign = 0b111111;

    for (uint8_t i = 0; i < 6; i++)
    {
        if(stroke_vel[i] < 0)
        {
            sign &= ~(1UL << i);
            out_vel[i] = (uint16_t)(-1. * stroke_vel[i] * 1000000. + 0.5);
        }
        else
        {
            out_vel[i] = (uint16_t)(stroke_vel[i] * 1000000. + 0.5);
        }
        out_len[i] = (uint16_t)(stroke_len[i] * 100000. + 0.5);
    }

    // Length
    tx_len1.data[0] = (uint8_t)(out_len[0] >> 8);   // Actuator 1
    tx_len1.data[1] = (uint8_t) out_len[0];
    tx_len1.data[2] = (uint8_t)(out_len[1] >> 8);   // Actuator 2
    tx_len1.data[3] = (uint8_t) out_len[1];
    tx_len1.data[4] = (uint8_t)(out_len[2] >> 8);   // Actuator 3
    tx_len1.data[5] = (uint8_t) out_len[2];

    tx_len2.data[0] = (uint8_t)(out_len[3] >> 8);   // Actuator 4
    tx_len2.data[1] = (uint8_t) out_len[3];
    tx_len2.data[2] = (uint8_t)(out_len[4] >> 8);   // Actuator 5
    tx_len2.data[3] = (uint8_t) out_len[4];
    tx_len2.data[4] = (uint8_t)(out_len[5] >> 8);   // Actuator 6
    tx_len2.data[5] = (uint8_t) out_len[5];

    // Velocity
    tx_vel1.data[0] = (uint8_t)(out_vel[0] >> 8);   // Actuator 1
    tx_vel1.data[1] = (uint8_t) out_vel[0];
    tx_vel1.data[2] = (uint8_t)(out_vel[1] >> 8);   // Actuator 2
    tx_vel1.data[3] = (uint8_t) out_vel[1];
    tx_vel1.data[4] = (uint8_t)(out_vel[2] >> 8);   // Actuator 3
    tx_vel1.data[5] = (uint8_t) out_vel[2];
    tx_vel1.data[6] = sign & 0b000111;      // bit mask for the sign of the 3 first actuators

    tx_vel2.data[0] = (uint8_t)(out_vel[3] >> 8);   // Actuator 4
    tx_vel2.data[1] = (uint8_t) out_vel[3];
    tx_vel2.data[2] = (uint8_t)(out_vel[4] >> 8);   // Actuator 5
    tx_vel2.data[3] = (uint8_t) out_vel[4];
    tx_vel2.data[4] = (uint8_t)(out_vel[5] >> 8);   // Actuator 6
    tx_vel2.data[5] = (uint8_t) out_vel[5];
    tx_vel2.data[6] = sign >> 3;            // bit shift for the 3 last actuators


    write(this->socket_, &tx_len1, sizeof(struct can_frame));
    usleep(500);
    write(this->socket_, &tx_len2, sizeof(struct can_frame));
    usleep(500);
    write(this->socket_, &tx_vel1, sizeof(struct can_frame));
    usleep(500);
    write(this->socket_, &tx_vel2, sizeof(struct can_frame));
}

bool CANbus::recv_data(double stroke_len[], uint8_t* ampere)
{
    struct can_frame rx_frame;

    bool msg1 = false;
    bool msg2 = false;


    recv(socket_, &rx_frame, sizeof(struct can_frame), MSG_DONTWAIT);

    uint8_t j = 0;

    if (rx_frame.can_id == 0xF0)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            uint16_t in_len = rx_frame.data[j] << 8;
            in_len += rx_frame.data[j + 1];

            stroke_len[i] = (float) in_len / 100000.;

            j += 2;
        }
        msg1 = true;
    }

    if (!msg1) return false;

    recv(socket_, &rx_frame, sizeof(struct can_frame), MSG_DONTWAIT);

    if (rx_frame.can_id == 0xF1)
    {
        j = 0;

        for (uint8_t i = 3; i < 6; i++)
        {
            uint16_t in_len = rx_frame.data[j] << 8;
            in_len += rx_frame.data[j + 1];

            stroke_len[i] = (float) in_len / 100000.;

            j += 2;
        }
        *ampere = rx_frame.data[6];
        msg2 = true;
    }

    return msg1 && msg2;
}

void CANbus::rx_flush()
{
    struct can_frame rx_frame;
    int num_bytes = 1;

    while (num_bytes > 0)
    {
        num_bytes = recv(socket_, &rx_frame, sizeof(struct can_frame), MSG_DONTWAIT);
    }
}











































