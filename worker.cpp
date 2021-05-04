#include "worker.h"

Worker::Worker(IMode* program, QObject *parent)
    : QObject(parent), m_runningProgram(program)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Worker::execute);




    /*
    Worker* worker = new Worker(m_workerProgram);
    worker->moveToThread(&workerThread);
    //connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread.start();

    connect(worker, &Worker::strokeRefChanged, this, &Controller::setStrokeRef);
    connect(worker, &Worker::warningChanged, this, &Controller::setWarningState);
    connect(this, &Controller::workerProgramChanged, worker, &Worker::setWorkerProgram);
    connect(this, &Controller::activatedChanged, worker, &Worker::runTimer);*/
}

void Worker::execute()
{
    static uint8_t msgCount = 0;
    static Eigen::Matrix<double, 2, 6> output;
    static double len[6] = { 0., 0., 0., 0., 0., 0. };
    static double vel[6] = { 0., 0., 0., 0., 0., 0. };
    static QVector<double> strokeRef;
    static bool warn = false;

    msgCount++;

    output = m_runningProgram->sample();

    m_ik.calc_legs(output);

    for (int i = 0; i < 6; i++)
    {
        len[i] = output(0, i);
        vel[i] = output(1, i);

        warn = len[i] > 0.089 || len[i] < 0.001;
    }

    m_can.send_data(len, vel);


    if (msgCount >= 10)
    {
        for (uint8_t i = 0; i < 6; i++)
        {
            strokeRef.insert(i, len[i] * 1000.);
        }
        emit strokeRefChanged(strokeRef);
        emit warningChanged(warn);
        msgCount = 0;
    }
}


void Worker::setWorkerProgram(IMode* newWorkerProgram)
{
    m_runningProgram = newWorkerProgram;
    m_runningProgram->reset();
}

void Worker::runTimer(const bool& run)
{
    if(run && !m_timer->isActive()) m_timer->start(10);
    else if (!run && m_timer->isActive()) m_timer->stop();
}




