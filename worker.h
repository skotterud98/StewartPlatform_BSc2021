#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QVector>

#include <Eigen/Dense>
#include "inversekinematics.h"
#include "canbus.h"
#include "imode.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(IMode* program, QObject *parent = nullptr);
    ~Worker();

public slots:
    void execute();
    void setWorkerProgram(IMode* newWorkerProgram);
    void runTimer(const bool& run);

signals:
    void strokeRefChanged(const QVector<double>& newStrokeRef);
    void strokeFbChanged(const QVector<double>& newStrokeFb);
    void warningChanged(const bool& newWarningState);
    void ampereChanged(const int& newAmpere);
    void canReadChanged(const bool& newReadState);

private:
    IMode* m_runningProgram;
    QTimer* m_timer;
    CANbus m_can;
    InverseKinematics m_ik;
};

#endif // WORKER_H
