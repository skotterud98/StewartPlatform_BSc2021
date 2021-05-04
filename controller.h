#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QVector>
#include <QString>
#include <QProcess>

// QProcess process;
// process.startDetached("shutdown -P now");

#include "imode.h"
#include "neutral.h"
#include "oscillator.h"
#include "worker.h"
#include "park.h"
#include "joystick.h"


class Controller : public QObject
{
    // marker for MOC
    Q_OBJECT
    QThread workerThread;

    //Q_PROPERTY(double time READ getTime)
    Q_PROPERTY(double surgeOut READ getSurgeOut)
    Q_PROPERTY(double swayOut READ getSwayOut)
    Q_PROPERTY(double heaveOut READ getHeaveOut)
    Q_PROPERTY(double rollOut READ getRollOut)
    Q_PROPERTY(double pitchOut READ getPitchOut)
    Q_PROPERTY(double yawOut READ getYawOut)

    Q_PROPERTY(QVector<double> strokeRef READ getStrokeRef NOTIFY strokeRefChanged)

    Q_PROPERTY(bool activated MEMBER m_activated NOTIFY activatedChanged)
    Q_PROPERTY(bool warning MEMBER m_warning NOTIFY warningChanged)

    Q_PROPERTY(QString runningProgram MEMBER m_runningProgram NOTIFY runningProgramChanged)

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    explicit Controller(Oscillator* oscillator, Joystick* joystick, QObject *parent = nullptr);
    ~Controller();

    double getSurgeOut() const;
    double getSwayOut() const;
    double getHeaveOut() const;
    double getRollOut() const;
    double getPitchOut() const;
    double getYawOut() const;

    //double getTime() const;

    QVector<double> getStrokeRef() const;

public slots:
    void setStrokeRef(const QVector<double>& newStrokeRef);
    void setProgram(const QString& newProgram);
    void setWarningState(const bool& newWarningState);

signals:
    void activatedChanged(const bool& run);
    void strokeRefChanged(const QVector<double>& newStrokeRef);
    void warningChanged(const bool& newWarningState);
    void workerProgramChanged(IMode* newWorkerProgram);
    void runningProgramChanged(const QString& newRunningProgram);

private:
    Neutral* m_neutral;
    Park* m_park;
    Oscillator* m_oscillator;
    Joystick* m_joystick;

    IMode* m_workerProgram;

    bool m_activated;
    bool m_warning;

    QVector<double> m_strokeRef;

    QString m_runningProgram;
};

#endif // CONTROLLER_H
