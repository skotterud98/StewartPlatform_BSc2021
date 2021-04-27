#ifndef THREAD_H
#define THREAD_H

#include <QThread>

#include "canbus.h"
#include "oscillator.h"
#include "inversekinematics.h"

class Thread : public QThread
{
public:
    Thread();
    void run() override;

    Oscillator* get_obj();

private:
    CANbus* can;
    InverseKinematics* ik;
    Oscillator* oscillator;
};

#endif // THREAD_H
