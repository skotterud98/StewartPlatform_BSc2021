#ifndef CANBUS_H
#define CANBUS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <QDebug>


class CANbus
{
public:
    CANbus();
    ~CANbus();

    void send_data(const double stroke_len[], const double stroke_vel[]);
    bool recv_data(double stroke_len[], uint8_t* ampere);

    void rx_flush();

private:
    int socket_;
    struct sockaddr_can addr;
    struct ifreq ifr;

    struct can_frame tx_len1;
    struct can_frame tx_len2;
    struct can_frame tx_vel1;
    struct can_frame tx_vel2;
};

#endif // CANBUS_H
