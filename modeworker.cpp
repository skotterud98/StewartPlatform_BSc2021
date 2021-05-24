#include "modeworker.h"

ModeWorker::ModeWorker(IMode* program, QObject *parent)
    : QObject(parent), m_runningProgram(program)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ModeWorker::execute);
}

ModeWorker::~ModeWorker()
{
    delete m_timer;
}

void ModeWorker::execute()
{
    static uint8_t msgCount = 0;
    static Eigen::Matrix<double, 2, 6> output;
    static double len[6] = { 0., 0., 0., 0., 0., 0. };
    static double vel[6] = { 0., 0., 0., 0., 0., 0. };
    static double fb_len[6];
    static uint8_t current;
    static uint8_t rxErrCount = 0;

    QVector<double> strokeRef;
    QVector<double> strokeFb;

    bool warn = false;

    msgCount++;

    output = m_runningProgram->sample();

    m_ik.calc_legs(output);

    for (int i = 0; i < 6; i++)
    {
        len[i] = output(0, i);
        vel[i] = output(1, i);

        warn |= (len[i] > 0.088 || len[i] < 0.002);
    }

    m_can.send_data(len, vel);
    usleep(500);

    bool read_succeed = false;

    if (!(read_succeed |= m_can.recv_data(fb_len, &current))) rxErrCount++;


    if (msgCount >= 10)
    {
        for (uint8_t i = 0; i < 6; i++)
        {
            strokeRef.insert(i, len[i] * 1000.);

            strokeFb.insert(i, fb_len[i] * 1000.);
        }
        emit strokeRefChanged(strokeRef);
        emit strokeFbChanged(strokeFb);
        emit warningChanged(warn);
        emit ampereChanged(current);
        emit canReadChanged(read_succeed);
        msgCount = 0;
    }


    if (rxErrCount >= 5)
    {
        m_can.rx_flush();
        rxErrCount = 0;
    }
}


void ModeWorker::setWorkerProgram(IMode* newWorkerProgram)
{
    m_runningProgram = newWorkerProgram;
    m_runningProgram->reset();
}

void ModeWorker::runTimer(const bool& run)
{
    if(run && !m_timer->isActive()) m_timer->start(10);
    else if (!run && m_timer->isActive()) m_timer->stop();
}




