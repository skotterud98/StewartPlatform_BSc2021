#include "worker.h"

Worker::Worker(IMode* m_program, QObject *parent)
    : QObject(parent), m_programWorker(m_program)
{
    m_can = new CANbus;
    m_ik = new InverseKinematics;

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Worker::run);

    m_timer->start(10);
}

void Worker::run()
{
    static Eigen::Matrix<double, 2, 6> output;
    static double len[6] = { 0., 0., 0., 0., 0., 0. };
    static double vel[6] = { 0., 0., 0., 0., 0., 0. };

    m_can->send_data(len, vel);

    output = m_programWorker->sample();

    m_ik->calc_output(output);

    for (int i = 0; i < 6; i++)
    {
        len[i] = output(0, i);
        vel[i] = output(1, i);
    }
}
