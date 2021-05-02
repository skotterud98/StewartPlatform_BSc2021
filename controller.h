#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include "imode.h"
#include "oscillator.h"
#include "worker.h"


class Controller : public QObject
{
    // marker for MOC
    Q_OBJECT
    QThread workerThread;

    Q_PROPERTY(double time READ getTime)
    Q_PROPERTY(double surgeOut READ getSurgeOut)
    Q_PROPERTY(double swayOut READ getSwayOut)
    Q_PROPERTY(double heaveOut READ getHeaveOut)
    Q_PROPERTY(double rollOut READ getRollOut)
    Q_PROPERTY(double pitchOut READ getPitchOut)
    Q_PROPERTY(double yawOut READ getYawOut)

    Q_PROPERTY(double heaveBias READ getHeaveBias)

public:
    explicit Controller(Oscillator* oscillator, QObject *parent = nullptr);
    ~Controller();

    double getSurgeOut() const;
    double getSwayOut() const;
    double getHeaveOut() const;
    double getRollOut() const;
    double getPitchOut() const;
    double getYawOut() const;

    double getHeaveBias() const;

    double getTime() const;

signals:
    //void startTimeEvent();

private:
    Oscillator* m_oscillator;
    IMode* m_program;
};

#endif // CONTROLLER_H
