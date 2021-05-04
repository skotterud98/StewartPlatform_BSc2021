#include "controller.h"

Controller::Controller(Oscillator* oscillator, Joystick* joystick, QObject* parent)
    : QObject(parent), m_oscillator(oscillator), m_joystick(joystick)
{
    m_warning = false;

    m_neutral = new Neutral;
    m_park = new Park;

    m_workerProgram = m_park;
    m_runningProgram = "Park";

    Worker* worker = new Worker(m_workerProgram);
    worker->moveToThread(&workerThread);
    //connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread.start();

    connect(worker, &Worker::strokeRefChanged, this, &Controller::setStrokeRef);
    connect(worker, &Worker::warningChanged, this, &Controller::setWarningState);
    connect(this, &Controller::workerProgramChanged, worker, &Worker::setWorkerProgram);
    connect(this, &Controller::activatedChanged, worker, &Worker::runTimer);
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::setProgram(const QString& newProgram)
{
    m_workerProgram->reset();

    if (newProgram == "Park")
    {
        m_workerProgram = m_park;
        m_runningProgram = "Park";
    }
    if (newProgram == "Neutral")
    {
        m_workerProgram = m_neutral;
        m_runningProgram = "Neutral";
    }
    if (newProgram == "Sine Oscillator")
    {
        m_workerProgram = m_oscillator;
        m_runningProgram = "Sine Oscillator";
    }
    if (newProgram == "Joystick")
    {
        m_workerProgram = m_joystick;
        m_runningProgram = "Joystick";
    }

    emit workerProgramChanged(m_workerProgram);
    emit runningProgramChanged(m_runningProgram);
}


//double Controller::getTime() const { return m_workerProgram->getTime(); }

double Controller::getSurgeOut() const { return m_workerProgram->getInputPos(0) * 1000.; }

double Controller::getSwayOut() const { return m_workerProgram->getInputPos(1) * 1000.; }

double Controller::getHeaveOut() const { return m_workerProgram->getInputPos(2) * 1000.; }

double Controller::getRollOut() const { return m_workerProgram->getInputPos(3) * (180. / PI); }

double Controller::getPitchOut() const { return m_workerProgram->getInputPos(4) * (180. / PI); }

double Controller::getYawOut() const { return m_workerProgram->getInputPos(5) * (180. / PI); }


void Controller::setStrokeRef(const QVector<double>& newStrokeRef)
{
    if (newStrokeRef == m_strokeRef)
        return;
    m_strokeRef = newStrokeRef;
    emit strokeRefChanged(m_strokeRef);
}

QVector<double> Controller::getStrokeRef() const { return m_strokeRef; }

void Controller::setWarningState(const bool& newWarningState)
{
    if (newWarningState == m_warning)
        return;
    m_warning = newWarningState;
    emit warningChanged(m_warning);
}


















