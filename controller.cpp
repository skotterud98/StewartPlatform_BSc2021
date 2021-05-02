#include "controller.h"

Controller::Controller(Oscillator* oscillator, QObject* parent)
    : QObject(parent), m_oscillator(oscillator)
{
    m_program = m_oscillator;

    Worker* worker = new Worker(m_program);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    //connect(this, &Controller::startTimeEvent, worker, &Worker::doWork);
    workerThread.start();
    qDebug() << "thread started";
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

double Controller::getTime() const { return m_program->getTime(); }

double Controller::getSurgeOut() const { return m_program->getInputPos(0) * 1000.; }

double Controller::getSwayOut() const { return m_program->getInputPos(1) * 1000.; }

double Controller::getHeaveOut() const { return m_program->getInputPos(2) * 1000.; }

double Controller::getRollOut() const { return m_program->getInputPos(3) * (180. / PI); }

double Controller::getPitchOut() const { return m_program->getInputPos(4) * (180. / PI); }

double Controller::getYawOut() const { return m_program->getInputPos(5) * (180. / PI); }

double Controller::getHeaveBias() const { return (m_program->getHeaveBias()) * 1000.; }

/*

void Controller::run()
{
    static Eigen::Matrix<double, 2, 6> output;
    static double len[6] = { 0., 0., 0., 0., 0., 0. };
    static double vel[6] = { 0., 0., 0., 0., 0., 0. };

    m_can->send_data(len, vel);

    output = m_program->sample();

    output = m_ik->calc_output(output);

    for (int i = 0; i < 6; i++)
    {
        len[i] = output(0, i);
        vel[i] = output(1, i);
    }
}
*/
