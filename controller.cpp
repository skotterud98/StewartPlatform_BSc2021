#include "controller.h"

Controller::Controller(Oscillator* oscillator, Joystick* joystick, QObject* parent)
    : QObject(parent), m_oscillator(oscillator), m_joystick(joystick)
{
    m_ampere = 0;

    m_warning = false;
    m_activated = false;
    m_canReadState = false;

    m_workerProgram = &m_park;
    m_runningProgram = "Park";

    ModeWorker* worker = new ModeWorker(m_workerProgram);
    worker->moveToThread(&workerThread);
    //connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread.start();

    connect(worker, &ModeWorker::strokeRefChanged, this, &Controller::setStrokeRef);
    connect(worker, &ModeWorker::strokeFbChanged, this, &Controller::setStrokeFb);
    connect(worker, &ModeWorker::warningChanged, this, &Controller::setWarningState);
    connect(worker, &ModeWorker::ampereChanged, this, &Controller::setAmpere);
    connect(worker, &ModeWorker::canReadChanged, this, &Controller::setCanReadState);
    connect(this, &Controller::workerProgramChanged, worker, &ModeWorker::setWorkerProgram);
    connect(this, &Controller::activatedChanged, worker, &ModeWorker::runTimer);
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
        m_workerProgram = &m_park;
        m_runningProgram = "Park";
    }
    if (newProgram == "Neutral")
    {
        if (m_runningProgram == "Park") m_workerProgram = &m_rampneutral;
        else m_workerProgram = &m_neutral;
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

void Controller::setStrokeFb(const QVector<double> &newStrokeFb)
{
    if (newStrokeFb == m_strokeFb)
        return;
    m_strokeFb = newStrokeFb;
    emit strokeFbChanged(m_strokeFb);
}

QVector<double> Controller::getStrokeFb() const { return m_strokeFb; }

void Controller::setWarningState(const bool& newWarningState)
{
    if (newWarningState == m_warning)
        return;
    m_warning = newWarningState;
    emit warningChanged(m_warning);
}

uint8_t Controller::getAmpere() const { return m_ampere; }

void Controller::setAmpere(const int &newAmpere)
{
    if (newAmpere == m_ampere)
        return;
    m_ampere = newAmpere;
    emit ampereChanged(m_ampere);
}

bool Controller::getCanReadState() const { return m_canReadState; }

void Controller::setCanReadState(const bool &newCanReadState)
{
    if (newCanReadState == m_canReadState)
        return;
    m_canReadState = newCanReadState;
    emit canReadStateChanged(m_canReadState);
}

void Controller::shutdown()
{
    workerThread.quit();
    workerThread.wait();
    system("sudo shutdown now");
}


















