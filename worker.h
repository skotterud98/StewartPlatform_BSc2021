#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include <Eigen/Dense>
#include "inversekinematics.h"
#include "canbus.h"
#include "imode.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(IMode* m_program, QObject *parent = nullptr);

public slots:

    void run();

signals:
    //void resultReady();

private:
    QTimer* m_timer;
    IMode* m_programWorker;
    CANbus* m_can;
    InverseKinematics* m_ik;

};

#endif // WORKER_H
