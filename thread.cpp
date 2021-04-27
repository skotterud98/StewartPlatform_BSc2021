#include "thread.h"

Thread::Thread() :
    can(new CANbus), oscillator(new Oscillator),
    ik(new InverseKinematics)
{

}

void Thread::run()
{
    while (true)
    {
        static std::vector<std::vector<double>> output(2, std::vector<double>(6));
        static double t = 0.;
        static double pose[6];
        static double twist[6];
        static double len[6];
        static double vel[6];

        output = oscillator->sample_sine(t);
        t += 0.01;

        for (int i = 0; i < 6; i++)
        {
            pose[i] = output[POS][i];
            twist[i] = output[VEL][i];
        }

        ik->calc_output(output, pose, twist);

        for (int i = 0; i < 6; i++)
        {
            len[i] = output[POS][i];
            vel[i] = output[VEL][i];
        }

        can->send_data(len, vel);

        msleep(10);
    }
}

Oscillator* Thread::get_obj() { return oscillator; }
